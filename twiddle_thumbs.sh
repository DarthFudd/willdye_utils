#!/usr/bin/env bash
# Do nothing except increment a counter for ten seconds. This provides
# a very(!) rough estimate of CPU speed. For example, in 2016 a tiny
# embedded SOM ranked at 14, and a cheap desktop system ranked at 400.

echo "Twiddling thumbs (i.e. doing almost nothing) for 10 seconds..."

# If this code is ported to another language, beware of optimizers.
for (( x=0, SECONDS=0; SECONDS < 11; x++ ))
do :
done

echo "Done.  Twiddled thumbs $x times in 10 seconds.  In units of"
echo "kttps (thousand of thumb-twiddles per second), that's roughly:"
echo "$(( $x / 10000 ))"
