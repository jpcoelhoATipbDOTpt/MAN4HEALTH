function [id,json]=create_parcel(TerUri,parcelLoc)

% TerUri - URI do terreno onde a parcela se encontra
% parcelLoc - Identificador da localização da parcela (e.g. A5)

array=["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"];

prop = "Property";

%---------------------------------------------------------Gera ID
fp=fopen("ParID.txt",'a+');
TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
fclose(fp);

id = generateParAddr(array);
while(~isempty(find(contains(TextAsCells{1},id))))
    disp('ParAddr repetido... gerando novo');
    id = generateParAddr(array);
end

fp=fopen("ParID.txt",'a+');
fprintf(fp,"%s\r\n",id);
fclose(fp);

parcel.id = id;
parcel.type = "Parcel";

parcel.location.type="GeoProperty";
parcel.location.value.type="Point";
parcel.location.value.coordinates=[41.488698, -7.248216];

parcel.specification.type=prop;
parcel.specification.value = parcelLoc;

parcel.refTerrain.type="Relationship";
parcel.refTerrain.object=TerUri;

context = ', "@context" : [ "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld", "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Context/context-normalized.jsonld"]}';

x=jsonencode(parcel);
json=[x(1:end-1) context];

end

function [id]=generateParAddr(array)

id = "urn:ngsi-ld:Parcel:";
for j=1:8
    val=randi(length(array),1,1);
    id=id+array(val);
end
end