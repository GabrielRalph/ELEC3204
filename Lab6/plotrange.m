function plotrange(minv,maxv,options)
    arguments
        minv (1,1) {mustBeNumeric} = 1
        maxv (1,1) {mustBeNumeric} = 1
        options.unit {mustBeTextScalar} = ""
        options.precision {mustBeInteger} = 0
    end

    yline(minv, 'Label',funit(minv, options.unit), ...
        'LabelVerticalAlignment','bottom','LabelHorizontalAlignment','right', 'FontWeight','bold');
    yline(maxv, 'Label',funit(maxv, options.unit), ...
        'LabelVerticalAlignment','top','LabelHorizontalAlignment','right', 'FontWeight','bold');
end

