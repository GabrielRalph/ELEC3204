function snapylim(lims)
    ylim(lims)
    yt = yticks;
    
    y0 = yt(1);
    dt = yt(2) - y0;
    yn = yt(end);

    if y0 > lims(1) 
        y0 = y0 - dt;
        yt = cat(2, y0, yt);
    end
    if (yn < lims(2))
        yn = yn + dt;
        yt = cat(2, yt, yn);
    end
    
    yticks(yt);
    ylim([y0, yn]);
    
end