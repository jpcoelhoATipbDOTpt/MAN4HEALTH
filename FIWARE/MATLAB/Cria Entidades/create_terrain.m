function [id,json]=create_terrain(TerName)

% TerUri - URI do terreno onde a terraina se encontra
% terrainLoc - Identificador da localização da terraina (e.g. A5)

array=["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"];

prop = "Property";

%---------------------------------------------------------Gera ID
fp=fopen("TerID.txt",'a+');
TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
fclose(fp);

id = generateTerAddr(array);
while(~isempty(find(contains(TextAsCells{1},id))))
    disp('ParAddr repetido... gerando novo');
    id = generateTerAddr(array);
end

fp=fopen("TerID.txt",'a+');
fprintf(fp,"%s\r\n",id);
fclose(fp);

terrain.id = id;
terrain.type = "Terrain";

terrain.terrainSpecs.type=prop;
terrain.terrainSpecs.value.location.type="GeoProperty";
terrain.terrainSpecs.value.location.value.type="Point";
terrain.terrainSpecs.value.location.value.coordinates=[41.488698, -7.248216];

terrain.terrainSpecs.value.nearestLocation.type=prop;
terrain.terrainSpecs.value.nearestLocation.value=TerName;

terrain.terrainSpecs.value.terrainArea.type=prop;
terrain.terrainSpecs.value.terrainArea.value=2.5;

terrain.terrainSpecs.value.aditionalNotes.type=prop;
terrain.terrainSpecs.value.aditionalNotes.value="Terreno agricola perto de Mirandela com cultura de oliveiras";

terrain.address.type=prop;
terrain.address.value.ownerName.type=prop;
terrain.address.value.ownerName.value="---";

terrain.address.value.streetAddress.type=prop;
terrain.address.value.streetAddress.value="Rua ---";

terrain.address.value.postalCode.type=prop;
terrain.address.value.postalCode.value="XXXX-XXX";

terrain.address.value.addressLocality.type=prop;
terrain.address.value.addressLocality.value="Mirandela";

terrain.address.value.Country.type=prop;
terrain.address.value.Country.value="Portugal";

terrain.address.value.telephone.type=prop;
terrain.address.value.telephone.value="(+351) XXX XXX XXX";

terrain.address.value.email.type=prop;
terrain.address.value.email.value="XXXXXX@mail.pt";

context = ', "@context" : [ "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld", "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Context/context-normalized.jsonld"]}';

x=jsonencode(terrain);
json=[x(1:end-1) context];

end

function [id]=generateTerAddr(array)

id = "urn:ngsi-ld:terrain:";
for j=1:8
    val=randi(length(array),1,1);
    id=id+array(val);
end
end