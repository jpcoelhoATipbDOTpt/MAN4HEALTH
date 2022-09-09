function delete_tree_terrain(host,urn_terrain)

%% Terreno
h = waitbar(0,'Please wait...');

%% Parcelas nos terrenos
waitbar(0.2,h)
resposta=pesquisa_entidades_http_progress(host,'refTerrain',urn_terrain,true);
urn_parcel=[];
if ~isempty(resposta)
    urn_parcel=[urn_parcel ;string(char(resposta.id))];
end

%% Dispositivos nas parcelas
waitbar(0.4,h)
urn_device=[];
[n_parcel,~]=size(urn_parcel);
for nprcl=1: n_parcel
    resposta=pesquisa_entidades_http_progress(host,'refParcel',urn_parcel(nprcl,:),false);
    if ~isempty(resposta)
        urn_device=[urn_device ;string(char(resposta.id))];
    else
        urn_device=[];
    end
end

%% Hardware nos dispositivos
waitbar(0.6,h)
urn_hardware=[];
urn_type=[];
[n_device,~]=size(urn_device);
for ndvce=1: n_device
    resposta=pesquisa_entidades_http_progress(host,'refDevice',urn_device(ndvce,:),false);
    if ~isempty(resposta)
        if length(resposta)>1
            for i=1:length(resposta)
                urn_type=[urn_type; string(resposta{i}.type)];
                urn_hardware= [urn_hardware; string(resposta{i}.id)];
            end
        else
            urn_type=[urn_type; string(resposta.type)];
            urn_hardware = [urn_hardware; string(resposta.id)];
        end
    end
end

%% Cria Body
waitbar(0.7,h)
urn_total=[urn_terrain;urn_parcel;urn_device;urn_hardware];
urn_string="[";
for ntotl=1:length(urn_total)
    urn_string = urn_string + '"' + urn_total(ntotl) + '"' + ",";
end

urn_char=char(urn_string);
urn_char(end)=']';

% try
%     apaga_entidades_batch_http(urn_char,'/terrain');
% catch
%     disp('Erro');
%     return
%
% end
%% Apaga entidades
waitbar(0.8,h)
apaga_entidades_batch_http(host,urn_char,'/terrain');

% .... Remove entradas no ficheiro TerKeys.txt
remove_entradas_ficheiro(urn_terrain,"TerID.txt");
% .... Remove entradas no ficheiro ParKeys.txt
remove_entradas_ficheiro(urn_parcel,"ParID.txt");
% .... Remove entradas no ficheiro DevKeys.txt
remove_entradas_ficheiro(urn_device,"DevID.txt");
% .... Remove entradas nos ficheiro de hardware/sensores
hwr_filename=["LoRaID.txt";"BatID.txt";"MoistureID.txt"];
for nfile=1:length(hwr_filename)
    remove_entradas_ficheiro(urn_hardware,hwr_filename(nfile));
end

waitbar(1,h)
close(h)
end
