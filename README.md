# ML for DC_Motor_Control

A polynomial regression algorithm to stabilize the error between the User-given and Sensed-speed under no load and loaded conditions for a 12 V DC motor.


### Conventional method

I guess some Electronics stuff.

### Deploying Machine Learning 
 The behaviour of the DC motor is polymial as observed from the graph below.

<figure>
	<a href="http://farm9.staticflickr.com/8426/7758832526_cc8f681e48_b.jpg"><img src="Graph.png"></a>
	<figcaption><center>RPM vs PWM of 2 different 12V DC motors</a>.</center></figcaption>
</figure>

* Obtain the coefficients of the polynomial function using polynomial regression.
* Recreate the function in arudino.