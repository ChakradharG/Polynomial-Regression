# Polynomial Regression
Perform polynomial curve fitting on a given data set and visualize the output.
The code calculates the learning rate depending upon the order of the output polynomial that the user desires. (Works well for polynomials upto order 3-4, for higher order polynomials, the loss function diverges unless the learning rate is manually fed). The code can handle both, inputs & outputs in terminal and from files.

<br>

## Getting Started
* Clone this repository
* Compile ```PolynomialRegression.cpp``` (g++ ```PolynomialRegression.cpp``` -o ```Main.exe```)
* Run ```Fit.bat```

<br>

## How to Use
* Change the ```Input.txt``` file according to the desired data set (Refer to the format section)
* Make sure ```Rscript.exe``` is added to PATH or else provide absolute path in ```Fit.bat```
* Run ```Fit.bat```

(Note: If you are not using Windows, you would have to run the commands in ```Fit.bat``` individually in your terminal)

<br>

## Format of Input.txt
* Line 1: Size of the sample data (Number of data points)
* Line 2: X data points
* Line 3: Y data points
* Line 4: Desired order of the output polynomial
* Line 5: Learning rate alpha (optional, if you want to use this then uncomment corresponding lines in the PolynomialRegression.cpp)

<br>

## Format of Output.txt
* Column 1: X data points
* Column 2: Y data points
* Column 3: Hypothesis function yh for different data points

<br>

## Example Output
![](Example/Rplot.png)
