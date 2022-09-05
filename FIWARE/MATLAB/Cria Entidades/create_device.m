function [id,json]=create_device(ParUri)

% ParUri - URI da parcela

array=["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"];

prop = "Property";

%---------------------------------------------------------Gera ID
fp=fopen("DevID.txt",'a+');
TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
fclose(fp);

id = generateDevAddr(array);
while(~isempty(find(contains(TextAsCells{1},id))))
    disp('DevAddr repetido... gerando novo');
    id = generateDevAddr(array);
end

fp=fopen("DevID.txt",'a+');
fprintf(fp,"%s\r\n",id);
fclose(fp);

device.id = id;
device.type = "Device";

t = datetime('now', 'TimeZone', 'local');
device.dateInstalled.type=prop;
device.dateInstalled.value = datestr(t,'yyyy-mm-ddTHH:MM:ss.FFFZ');

device.specification.type=prop;
device.specification.value="Dispositivo IoT";

device.hardware.type=prop;

device.hardware.value.CPU.type=prop;
device.hardware.value.CPU.value="ATMega328";

device.hardware.value.hardwareVersion.type=prop;
device.hardware.value.hardwareVersion.value="1.0";

device.hardware.value.firmwareVersion.type=prop;
device.hardware.value.firmwareVersion.value="1.0";

device.refParcel.type="Relationship";
device.refParcel.object=ParUri;

context = ', "@context" : [ "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld", "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Context/context-normalized.jsonld"]}';

x=jsonencode(device);
json=[x(1:end-1) context];

end

function [id]=generateDevAddr(array)

id = "urn:ngsi-ld:Device:";
for j=1:8
    val=randi(length(array),1,1);
    id=id+array(val);
end
end