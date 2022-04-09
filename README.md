# cstrike-random-number-generator
A reverse-engineered version of RNG (Random Number Generator) algorithm that is being used within cstrike.

The code is reverse-engineered from the client.dll using IDA pro.

# Description
The code that is presented here is used to calculate weapon spread. Therefore, it can be used to simulate frame-perfect spread values given the same seed as original. The engine iself also has a RNG built in it (*RandomFloat* & *RandomLong* functions), however these ones differs from our one.

The engine RNG doens't use seed table, therefore cannot generate the same output as the cstrike one given the same seeds. That makes it really "random", but for our purposes (weapon spread) - it cannot be fully random. It has to output the same number many frames afterwareds, when the input is the same seed as before.

These two functions are being actively used, when firing a weapon. That is in functions like: *CG3SG1::G3SG1Fire*, *CSG550::SG550Fire* and *FireBullets3*, which simulates the bullet shot.

Theres a pseudocode snapshot for *FireBullets3*.

```c++
unsigned int v8;
int v9;
float v10;
float v11;
float v12;
float v13;
float x;
v8 = seed;
v9 = a1;
if ( a2 ) // If it's a player entity
{
  v10 = UTIL_SharedRandomFloat(seed, -0.5, 0.5);
  x = UTIL_SharedRandomFloat(v8 + 1, -0.5, 0.5) + v10;
  v11 = UTIL_SharedRandomFloat(v8 + 2, -0.5, 0.5);
  a7 = UTIL_SharedRandomFloat(v8 + 3, -0.5, 0.5) + v11;
}
else // For monsters and non-player entities (turrets, ...)
{
  do
  {
    // These are incorrectly guessed floaint-point values by IDA.
    // Here we're using the engine's RNG.
    (g_engfuncs.pfnRandomFloat)(-1090519040, 1056964608, *&result, *&a5);
    v12 = result;
    (g_engfuncs.pfnRandomFloat)(-1090519040, 1056964608);
    result = result + v12;
    x = result;
    (g_engfuncs.pfnRandomFloat)(-1090519040, 1056964608);
    v13 = result;
    (g_engfuncs.pfnRandomFloat)(-1090519040, 1056964608);
    a7 = a7 + v13;
  }
  while ( x * x + a7 * a7 > 1.0 );
}
*(v9 + 8) = 0;
*v9 = *&retstr * x;
*(v9 + 4) = a7 * *&retstr;
return result;
```
