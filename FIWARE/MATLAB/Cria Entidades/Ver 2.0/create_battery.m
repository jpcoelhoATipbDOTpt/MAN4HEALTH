function [id,json]=create_battery(DevUri)

array=["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"];

prop = "Property";

%---------------------------------------------------------Gera ID
fp=fopen("BatID.txt",'a+');
TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
fclose(fp);

id = generateBatAddr(array);
while(~isempty(find(contains(TextAsCells{1},id))))
    disp('DevAddr repetido... gerando novo');
    id = generateDevAddr(array);
end

fp=fopen("BatID.txt",'a+');
fprintf(fp,"%s\r\n",id);
fclose(fp);

battery.id = id;
battery.type = "Battery";

battery.batteryLevel.type = prop;
battery.batteryLevel.value = 0.8;
battery.batteryLevel.unitCode = "P1";
t = datetime('now', 'TimeZone', 'local');
battery.batteryLevel.observedAt = datestr(t,'yyyy-mm-ddTHH:MM:ss.FFFZ');

battery.batteryTechnology.type = prop;
battery.batteryTechnology.value = "LiIOn";

battery.batteryCharge.type = prop;
battery.batteryCharge.value = 1800;
battery.batteryCharge.unitCode = "E09";


battery.refDevice.type = "Relationship";
battery.refDevice.object = DevUri;


context = ', "@context" : [ "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld", "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Context/context-normalized.jsonld"]}';

x=jsonencode(battery);
json=[x(1:end-1) context];

end

function [id]=generateBatAddr(array)

id = "urn:ngsi-ld:battery:";
for j=1:8
    val=randi(length(array),1,1);
    id=id+array(val);
end
end
