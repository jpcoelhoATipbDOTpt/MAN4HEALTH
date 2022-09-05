function cnt=remove_entradas_ficheiro(urn_list,filename)

% Retorna a numero de unidades eliminadas. Em teoria deve ser igual ao
% tamanho de urn_list

% (c)2022 Coelho

% .... Remove entradas no ficheiro LoRaKeys.txt
[n_list,~]=size(urn_list);
cnt=0;
if n_list>0
    fp=fopen(filename,'r');
    TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
    fclose(fp);
    for lst=1:n_list
        inx=find(contains(TextAsCells{1},urn_list(lst,:)));
        if ~isempty(inx)
            TextAsCells{1}(inx)=[];
            cnt=cnt+1;
        end
    end
    fp=fopen(filename,'w');
    fprintf(fp,"%s\r\n",TextAsCells{1}{:});
    fclose(fp);
end