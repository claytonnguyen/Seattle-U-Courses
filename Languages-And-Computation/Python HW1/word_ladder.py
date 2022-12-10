# Clayton Nguyen
# word_ladder.py
# April 11, 2022

# Finds a word ladder from one word to another based on words 
# given by a text file. The words in the word ladder must be one letter
# off from the previous word in the ladder

from collections import deque

# process the file and the words in the file into a set
def processFile(wordList, pairs):
    for line in open("words.txt"): 
        line = line.rstrip()
        wordList.add(line)

    for l in open("pairs.txt"):
        l = l.rstrip()
        catch = l.split(' ')
        pairs.append(catch)

# find the actual word ladder, if none can be found, error message is printed
def findLadder(wordList, pairs):
    # Go through each pair of words and find a word ladder for them
    for x in range(len(pairs)):
        wordArr = wordList
        wordLadder = [pairs[x][0]]
        beginning = pairs[x][0]
        search = pairs[x][1]

        print('** Looking for ladder from ' + beginning + ' to ' + search)
        # Error if the words are not of equal lengths
        if len(pairs[x][0]) != len(pairs[x][1]):
            print('Cannot find word ladder of two different lengths')
        else:
            alph = 'abcdefghijklmnopqrstuvwxyz'
            found = False
            visited = set()
            q = deque()
            q.append(wordLadder)

            # Visits every list in the queue searching for a one off word that leads to the search word
            # till all the lists are popped off 
            while(len(q) > 0):
                ladder = q.popleft()
                oneOffs = []
                start = ladder[-1]
                visited.add(start)
                
                # check all the combinations of the start word
                # if the word is one off add to the list of one offs
                for r in range(len(start)):
                    word = start
                    for p in range(len(alph)):
                        word = word[:r] + alph[p] + word[r + 1:]
                        if word in wordArr and word not in visited:
                            oneOffs.append(word)

                # if the word is equal to the search word,
                # imediately pop and append word to print, then break out of loop
                for x in range(len(oneOffs)):
                    if oneOffs[x] == search:
                        ladder.append(oneOffs[x])
                        found = True
                        print("The ladder is: ", end="")
                        count = 0
                        for k in range(len(ladder)):
                            if count < len(ladder) - 1:
                                print(ladder[k] + ' -> ', end="")
                            else:
                                print(ladder[k], end="")
                            count += 1
                            # print("The ladder is: ", end="")
                            # print(ladder[k] + " -> ", end="")
                        break


                if found == True:
                    break

                # go through the list of one offs, make a new copy with new word appended,
                # add to the queue
                for x in range(len(oneOffs)):
                    temp = [d for d in ladder]
                    temp.append(oneOffs[x])
                    q.append(temp)

            if not found:
                print('PROGRAM CANNOT FIND A WORD LADDER FOR THE WORDS: ' + beginning + ' -> ' + search)
        print('')
        print('')

def main():
    wordList = set()
    pairs = []

    processFile(wordList, pairs)
    findLadder(wordList, pairs)

    


if __name__ == '__main__':
    main()