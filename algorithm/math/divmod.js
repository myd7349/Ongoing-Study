// 2017-09-14T15:05+08:00

// An example demonstrates how to write your own `divmod` in a recursive way.

function divmod(x, y) {
    // if x < y then
    //     q <- 0, r <- x
    // else
    //     q' <- x/2y, r' <- x mod 2y
    //
    //     if r' < y then
    //         q <- 2q', r <- r'
    //     else 
    //         q <- 2q' + 1, r <- r' - y

    if (x < y) {
        return [0, x];
    } else {
        var q_, r_;
        [q_, r_] = divmod(x, 2 * y);

        if (r_ < y)
            return [2 * q_, r_];
        else
            return [2 * q_ + 1, r_ - y];
    }
}

// References:
// C Interfaces and Implementations 17.2
