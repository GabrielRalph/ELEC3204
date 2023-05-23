function [minv, maxv] = brange(y, s)
    arguments 
        y (:, :) {mustBeNumeric} = 1
        s (1, 1) {mustBePositive} = 5
    end
    res = 0;
    y = reshape(y, [], 1);
    for i = 1:s
        res = res + y(i:(end - s + i));
    end
    res = res / s;

    minv = min(res);
    maxv = max(res);


end

