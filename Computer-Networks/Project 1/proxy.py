from socket import * 
from urllib.parse import urlparse 
import sys 
from pathlib import Path


def main():
    # default hostname and portNum for the program
    # portNum based on the equation 10000 + (4083344 % 2022)
    hostname = ''
    portNum = 10926

    if sys.argv[1]:
        portNum = int(sys.argv[1])

    # create server socket

    server_socket = socket(AF_INET, SOCK_STREAM)
    server_socket.bind(('', portNum))
    server_socket.listen(2)

    print('**************** Ready to serve... *********************')
    cur_dir = Path.cwd()
    p = cur_dir / Path('./cache')
    p.mkdir(parents=True, exist_ok=True)
    http_warning = 'HTTP 500 Internal Error \r\nHTTP request is malformed or not supported'
    while True:
        conn_socket, addr = server_socket.accept()
        print('Received a client connection from: ' + str(addr))

        sentence = conn_socket.recv(1024).decode()
        print('Client message is: ' + sentence)

        # error detection for the client input
        message = sentence.split(' ')
        if len(message) == 3:
            o = urlparse(message[1])
        else:
            http_malformed = http_warning + ', format: GET http://www.zhiju.me/networks/valid.html HTTP/1.0\r\n'
            conn_socket.send(http_warning.encode())
            pass
        if message[0].upper() not in 'GET':
            http_request = http_warning + ": use 'GET' HTTP request\r\n"
            conn_socket.send(http_request.encode())
            pass
        if message[2] not in 'HTTP/1.0\r\n':
            http1warning = http_warning + ': use HTTP/1.0\r\n'
            conn_socket.send(http1warning.encode())
            pass
        # parsing the user input url
        scheme = o.scheme # HTTP/1.0
        hostname = o.hostname # zhiju.me
        port = 80
        pathway = o.path # /networks/valid.html

        # block of code gets the subfolder path to put the cached files in
        fileUrl = pathway.split('/')
        file = fileUrl[-1] # filename ex. valid.html
        fileway = fileUrl[:-1] #filepath up to the filename ex. zhiju.me/networks
        filePath ="".join(fileway)
        subfolder = "./" + hostname + "-" + filePath

        # create the subfolder cache directory
        q = p / Path(subfolder)
        q.mkdir(parents=True, exist_ok=True)
        filename = q / Path('./' + file)

        # find if the file exists in the current file structure
        # ./cache/hostname/filename

        # file exists in the file structure
        if filename.exists():
            final = ""
            with filename.open("r") as f:
                from_file = f.readlines()
                final = "".join(from_file)

            print("Yeah! The requested file is in the cache and is about to be sent to the client!")
            conn_socket.send(final.encode())

        # file does not exist in the file structure
        else:
            # create a socket to connect to server
            proxy_socket = socket(AF_INET, SOCK_STREAM)
            proxy_socket.connect((hostname, port))

            # GET http://zhiju.me/networks/valid.html HTTP/1.0
            print('Oops! No cache hit! Requesting the server for the file...')
            req = "GET " + pathway + " HTTP/1.0\r\nHost: " + hostname + "\r\nConnection: close\r\n\r\n"
            print('Sending the following message from proxy to server: ')
            print(req)
            proxy_socket.send(req.encode())

            # get all the info from the request sent to server
            received = proxy_socket.recv(4096).decode()
            split_by_space = received.split(' ')
            status_code = int(split_by_space[1])
            split_by_line = received.split('\n')
            length = len(split_by_line)
            response_header = split_by_line[0]
            response_body_list = split_by_line[6:length]
            response_body = "".join(response_body_list)
            uncached = ""


            no_cache_error = 'Response received from the server, but status code is not 200! No cache writing...\n' \
                             'Now responding the client...'

            # error detection with the status code,
            # 200 is the only status code where caching is allowed
            if status_code == 200:
                print('Response received from server, and status code is 200! Writing to cache, save time next time.')
                print('File cached! Now responding the client with the requested file...')
                uncached = response_header + "\r\nCache-Hit: 0\r\n" + response_body + "\r\n\r\n"
                cached = response_header + "Cache-Hit: 1\n" + response_body + "\n\n"
                with filename.open("w") as f:
                    f.write(cached)
            elif status_code == 404:
                uncached = response_header + "\r\nCache-Hit: 0\r\n" + "404 NOT FOUND\r\n\r\n"
                print(no_cache_error)
            else:
                uncached = response_header + "\r\nCache-Hit: 0\r\n" + "Unsupported Error\r\n\r\n"
                print(no_cache_error)
            conn_socket.send(uncached.encode())
            proxy_socket.close()
        print("All done! Closing socket...")
        conn_socket.close()



if __name__ == '__main__':
    main()