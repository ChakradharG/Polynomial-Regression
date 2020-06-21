setwd('Working-directory')
dataPts <- read.csv('Output.csv')

plot(dataPts$X, dataPts$Y, 
	 col='blue', pch=16, 
	 main='Polynomial Regression',
	 xlab='X', ylab='Y')
lines(dataPts$X, dataPts$Yh, col='red')

l <- c('Ground truth', 'Hypothesis')
legend('bottomright', legend=l, col=c('blue', 'red'), pch=16)