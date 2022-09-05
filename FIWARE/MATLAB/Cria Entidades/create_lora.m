function [id,json]=create_lora(DevUri)

% y - Saída (JSON) formato array de carateres.

array=["0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"];

prop = "Property";

%---------------------------------------------------------Gera ID e DevAddr
fp=fopen("LoRaID.txt",'a+');
TextAsCells = textscan(fp, '%s %s %s %s', 'Delimiter', '\t');
fclose(fp);

[id,DevAddr] = generateLoraAddr(array);

while(~isempty(find(contains(TextAsCells{2},DevAddr))))
    disp('LoraAddr repetido... gerando novo');
    [id,DevAddr] = generateLoraAddr(array);
end

lora.id = id;
lora.type = "LoRa";
%--------------------------------------------------------------Gera NwkSkey
NwkSkey = "{";

for i=1:16
    NwkSkey = NwkSkey + "0x";
    for j=1:2
        val=randi(length(array),1,1);
        NwkSkey = NwkSkey + array(val);
    end
    if i==16
        NwkSkey = NwkSkey + "}";
    else
        NwkSkey = NwkSkey + ", ";
    end
end

%--------------------------------------------------------------Gera AppSkey
AppSkey = "{";

for i=1:16
    AppSkey = AppSkey + "0x";
    for j=1:2
        val=randi(length(array),1,1);
        AppSkey = AppSkey + array(val);
    end
    if i==16
        AppSkey = AppSkey + "}";
    else
        AppSkey = AppSkey + ", ";
    end
end
%----------------------------------------------------------------------RSSI
lora.rssi.type=prop;

lora.rssi.value.measuredvalue.type=prop;
lora.rssi.value.measuredvalue.value=0;
t = datetime('now', 'TimeZone', 'local');
lora.rssi.value.dateObserved.type=prop;
lora.rssi.value.dateObserved.value = datestr(t,'yyyy-mm-ddTHH:MM:ss.FFFZ');

lora.abp.type=prop;
lora.abp.value.NwkSkey.type = prop;
lora.abp.value.NwkSkey.value = NwkSkey;

lora.abp.value.AppSkey.type = prop;
lora.abp.value.AppSkey.value = AppSkey;

lora.abp.value.DevAddr.type = prop;
lora.abp.value.DevAddr.value = DevAddr;

lora.refDevice.type = "Relationship";
lora.refDevice.object = DevUri;

context = ', "@context" : [ "https://uri.etsi.org/ngsi-ld/v1/ngsi-ld-core-context.jsonld", "https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Context/context-normalized.jsonld"]}';

x=jsonencode(lora);
json=[x(1:end-1) context];

fp=fopen("LoRaID.txt",'a+');
fprintf(fp,"%s \t %s \t %s \t %s \r\n",id,DevAddr,NwkSkey,AppSkey);
fclose(fp);
end

function [id,DevAddr]=generateLoraAddr(array)

id = "urn:ngsi-ld:LoRa:";
DevAddr = "{";

    for i=1:4
        DevAddr = DevAddr + "0x";
        for j=1:2
            val=randi(length(array),1,1);
            DevAddr = DevAddr + array(val);
            id=id+array(val);
        end
        if i==4
            DevAddr = DevAddr + "}";
        else
            DevAddr = DevAddr + ", ";
        end
    end
end

