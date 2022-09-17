function parsedkey = parse(key)
    x=find(key=='x');
    c=find(key==',');
    parsedkey=key;
    parsedkey([x-1 x c c+1])=[];
    parsedkey([1 end])=[];
end