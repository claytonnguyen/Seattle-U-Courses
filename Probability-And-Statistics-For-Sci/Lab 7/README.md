# Confidence Intervals and Bootstrapping)

1. Create a random sample of size 10 from a normal distribution with u = 5 and o = 2. Calculate the sample mean and then construct a 95% confidence interval. Is the population mean covered by your confidence interval?
2. Create 100 random samples of size 10 from an exponential distribution with ^ = 2 and check the number of these samples for which the 95% confidence interval covers the population mean? Does this number align with the 95% confidence? Why or why not.
3. Create a single sample of size 20 from an exponential distribution with ^ = 2 then construct a 95% confidence level using bootstrapping with 10000 iterations.


We will use the payroll data from NYC to investigate confidence intervals. However, in this case we will be using bootstapping

1. Upload the NYC_Payroll2018.csv data set. This data set has both hourly, daily, and yearly rates. We are only concerned with the yearly rates. Filter the data set to only include the "per Annum" observations.
2. Create a sample of 15 employees and then use a QQ chart to verify that the sample data is normally distributed.
3. Calculate the sample mean and use bootstrapping with 10,000 iterations to create a 95% confidence interval for this estimation.
4. Is the population mean you calculated in part 3 within your confidence interval? If not, explain why this might be the case.
5. Create 20 different 15 employee samples and then bootstrap 95% confidence intervals using 10,000 iterations. How many of these 20 confidence intervals contain the population mean?
