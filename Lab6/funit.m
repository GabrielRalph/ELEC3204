function str = funit(value, qty, options)
    arguments
        value (1,1) {mustBeNumeric} = 1
        qty {mustBeText} = "N"
        options.precision {mustBeInteger} = 0
    end
    num = value;
    unum = 0;
    while (num > 1000) 
        num = num / 1000;
        unum = unum + 1;
    end
    while (abs(num) < 1)
        num = num * 1000;
        unum = unum - 1;
    end
    
    unitsa = ['k', 'M', 'G', 'T'];
    unitsb = ['m', 'u', 'n', 'p', 'f'];
    if (unum < 0)
        unum = unitsb(-unum);
    elseif (unum > 0) 
        unum = unitsa(anum);
    else
       unum = '' ;
    end
    
    str = sprintf("%.*f %c%s", options.precision, num, unum, qty);
end