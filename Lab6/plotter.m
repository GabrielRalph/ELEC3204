text = fileread("Oscilloscope.txt");
lines = splitlines(text);

for i = 1:length(lines)
    lines{i} = regexprep(lines{i}, '^\s+', "");
end
