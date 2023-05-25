classdef sdata
    %SIGNALDATA Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        y
        x

        xunits
        yunits

        xlabels
        ylabels
    end
    
    methods
        function obj = sdata(x0, y0, options)
            arguments
                x0 (:,:) {mustBeNumeric} = 1
                y0 (:,:) {mustBeNumeric} = 1
                options.xunits (:,1) {mustBeText} = {"mm"};
                options.yunits (:,1) {mustBeText} = {"mm"};

                options.xlabels (:,1) {mustBeText} = {"x"};
                options.ylabels (:,1) {mustBeText} = {"y"};
            end
            obj.x = x0;
            obj.y = y0;
            obj.xunits = options.xunits;
            obj.yunits = options.yunits;

            obj.xlabels = options.xlabels;
            obj.ylabels = options.ylabels;
        end

        function plot(obj, yidx, options)
            arguments
                obj sdata
                yidx (:,1) {mustBeNumericOrLogical} = 1
                options.xidx (1,1) {mustBeNumeric} = 1
            end
            y1 = obj.y(:, yidx);
            xidx = options.xidx;
            x1 = obj.x(:, xidx);
       
            [~, sn] = size(y1);
            for si = 1:sn
                hold on;
                plot(x1, y1(:, si), 'LineWidth',2);
            end
            
            yu = strjoin(unique(obj.yunits(yidx)), ", ");
            xlabel(sprintf("%s (%s)", obj.xlabels{xidx}, obj.xunits{xidx}));
            ylabel(yu);
            if sn > 1
                h = legend(obj.ylabels(yidx), 'Location','southoutside', 'Orientation','horizontal');
                h.AutoUpdate = false;
            end
        end
    end

    methods (Static)
        function resdata = open(filename) 
            text = fileread(filename);
            lines = splitlines(text);
            
            channels = regexp(lines{5}, '\w+', 'match');
            names = regexp(lines{6}, '\w+', 'match');
            tname = names(1);
            names = names(2:end);
            
            units = regexp(lines{7}, '\w+', 'match');
            x = cell2mat(cellfun(@(c) str2num(c), lines(8:end), 'UniformOutput',false));
            notoff = cell2mat(cellfun(@(c) ~strcmp(c, "Off"), names, 'UniformOutput',false));
            channels = channels(notoff);
            names = names(notoff);
            
            ylabels = names; %cellfun(@(a, b) sprintf('%s [%s]', a, b), names, channels, 'UniformOutput', false);
            
            resdata = sdata(x(:, 1), x(:, 2:end), "xlabels", tname, "xunits",units(1), ...
                              "ylabels",ylabels, "yunits",units(2:end));
        end
    end
end

