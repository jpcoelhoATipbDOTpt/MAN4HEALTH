function [id,json]=create_moisture(DevUri)

array=["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"];

prop = "Property";

%---------------------------------------------------------Gera ID
fp=fopen("MoistureID.txt",'a+');
TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
fclose(fp);

id = generateMoistureAddr(array);

while(~isempty(find(contains(TextAsCells{1},id))))
    disp('Addr repetido... gerando novo');
    id = generateMoistureAddr(array);
end

fp=fopen("MoistureID.txt",'a+');
fprintf(fp,"%s\r\n",id);
fclose(fp);

moisture.id = id;
moisture.type = "Moisture";

moisture.measuringMedium.type = prop;
moisture.measuringMedium.value = "soil";

moisture.dephtOrAltitude.type = prop;
moisture.dephtOrAltitude.value = -5;
moisture.dephtOrAltitude.unitCode = "CMT";

moisture.measurementValue.type = prop;
moisture.measurementValue.value = 65; % humidade relativa %
moisture.measurementValue.unitCode = "P1";
t = datetime('now', 'TimeZone', 'local');
moisture.measurementValue.observedAt = datestr(t,'yyyy-mm-ddTHH:MM:ss.FFFZ');

moisture.refDevice.type = "Relationship";
moisture.refDevice.object = DevUri;

context = ', "@context" : [ "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld", "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Context/context-normalized.jsonld"]}';

x=jsonencode(moisture);
json=[x(1:end-1) context];

end

function [id]=generateMoistureAddr(array)

id = "urn:ngsi-ld:Moisture:";
for j=1:8
    val=randi(length(array),1,1);
    id=id+array(val);
end
end
