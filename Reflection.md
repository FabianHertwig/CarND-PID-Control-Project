# Reflection

## What the parameters do

### P
P is proportional to the error. So a higher p will result in a more aggressive steering.

### I
I should prevent a systematic error. The simulator seems to be perfect (no systematic error) and therefore I could be zero or a really small number.


### D
D will dampen the steering when returning to the middle of the road so that the car will not overshoot.
When the car is oscillating it is a good idea to increase d.


## How the final parameters were chosen

I used a combination of using the twiddel algorithm to find good values and also tweaking them manually by my intuition of what the values do.