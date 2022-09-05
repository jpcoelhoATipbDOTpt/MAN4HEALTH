clear all;
clc;
% localhost = 127.0.0.1

% Começa por testar se o Orion se encontra ativo:
if ~testOrionBroker('http://localhost:1026/version')
    errordlg('Orion Broker not found!');
    return;
end

    
%% ------------------------------------------------------------------------
%  Cria entidade terreno
%  ------------------------------------------------------------------------
nterrain = 1; % Numero de terrenos
% Gera JSON combinado e guarda num ficheiro
nome_terreno=["Mirandela (Suçães)"];
numero_parcelas=[24];
tmp = "[";
for ntrn = 1: nterrain % Para cada terreno
    [terrain(ntrn).id,terrain(ntrn).json]=create_terrain(nome_terreno(ntrn));
    terrain(ntrn).nparcel=numero_parcelas(ntrn); % Numero de parcelas
    tmp = tmp + terrain(ntrn).json + ", ";
end
json = char(tmp);
json(end-1) = "]"; % Neste momento temos o body para instanciação batch das 
                   % entidades do tipo Terrain
fp = fopen('batch_body_terrain.json','w'); % Guarda body num ficheiro
fprintf(fp,"%s",json);
fclose(fp);
caminho ='/terrain';
resposta = gera_lote_entidades_no_orion(json,caminho);
% show(resposta)


%% ------------------------------------------------------------------------
%  Cria parcelas para cada terreno
%  ------------------------------------------------------------------------
% Isto tem que ser definido para cada terreno. Para este caso existe apenas
% um terreno...
coord_letras=["A","B","C","D"];
coord_numeros=["1","2","3","4","5","6"];
% Cria as etiquetas para cada parcela (pares letra + numero) e define o
% nunero de dispositivos
nprcl=1;
for i=1:length(coord_letras)
    for j=1:length(coord_numeros)
        ParList(nprcl)=coord_letras(i)+coord_numeros(j); 
        nprcl=nprcl+1;
    end
end

for ntrn=1:nterrain % Para cada terreno...
    for nprcl=1:terrain(ntrn).nparcel % Define etiquetas para as parcelas
        terrain(ntrn).parcel(nprcl).coord=ParList(nprcl);
        terrain(ntrn).parcel(nprcl).ndevice=1; % Define o numero de dispositivos IoT por parcela
    end
end
% Só para ilustrar a forma como uma determinada parcela pode ter mais que
% um dispositivo
terrain(1).parcel(1).ndevice=2;

% Cria o body para criação, em lote, de parcelas
tmp = "[";
for ntrn = 1: nterrain
    for nprcl=1:terrain(ntrn).nparcel
        % Cria entidade associada à terrain(ntrn).parcela(nprcl)
        [terrain(ntrn).parcel(nprcl).id,terrain(ntrn).parcel(nprcl).json]=create_parcel(terrain(ntrn).id,terrain(ntrn).parcel(nprcl).coord);
        tmp = tmp + terrain(ntrn).parcel(nprcl).json + ", ";
    end
end
json = char(tmp);
json(end-1) = "]"; % Neste momento temos o body para instanciação batch das 
                   % entidades do tipo Parcel
fp = fopen('batch_body_parcel.json','w'); % Guarda body num ficheiro
fprintf(fp,"%s",json);
fclose(fp);
caminho ='/terrain/parcel';
resposta = gera_lote_entidades_no_orion(json,caminho);
      
%% ------------------------------------------------------------------------
%  Cria dispositivos para cada parcela
%  ------------------------------------------------------------------------
% Isto tem que ser definido para cada parcela.

% Cria entidade associada a cada dispositivo para uma dada parcela

tmp = "[";
for ntrn=1:nterrain
    for nprcl=1:terrain(ntrn).nparcel
        for ndev=1:terrain(ntrn).parcel(nprcl).ndevice
            [terrain(ntrn).parcel(nprcl).device(ndev).id,terrain(ntrn).parcel(nprcl).device(ndev).json]=create_device(terrain(ntrn).parcel(nprcl).id);
            tmp = tmp + terrain(ntrn).parcel(nprcl).device(ndev).json + ", ";
        end
    end
end
        
json = char(tmp);
json(end-1) = "]"; % Neste momento temos o body para instanciação batch das 
                   % entidades do tipo device
fp = fopen('batch_body_device.json','w'); % Guarda body num ficheiro
fprintf(fp,"%s",json);
fclose(fp);
caminho ='/terrain/parcel/device';
resposta = gera_lote_entidades_no_orion(json,caminho);


% Nesta zona define-se o tipo de dispositivos que existe em cada terrain(1).parcela.
% neste momento isso é feito manualmente mas numa versão seguinte, cada
% nó IoT cria a sua própria entidade no Broker FIWARE

% Considera-se qie todas as parcelas têm um Device idêntico
for ntrn=1:nterrain % Para cada terreno...
    for nprcl=1:terrain(ntrn).nparcel % Cria as parcelas
        terrain(ntrn).parcel(nprcl).device(1).transceiver.tipo="lora";  % tipo de transceiver
        terrain(ntrn).parcel(nprcl).device(1).bateria.tipo = true;      % tem bateria?
        terrain(ntrn).parcel(nprcl).device(1).sensor.type=["Moisture","Temperature"];
        terrain(ntrn).parcel(nprcl).device(1).sensor.nsensor = length(terrain(ntrn).parcel(nprcl).device(1).sensor.type);

    end
end

% Apenas para ilustrar... algumas parcelas têm nais que um dispositivo específico
terrain(1).parcel(1).device(2).transceiver.tipo="none"; % Para já considera-se apenas um transceiver por Device mas no futuro pode-se altarar para vários
terrain(1).parcel(1).device(2).bateria.tipo = false;
terrain(1).parcel(1).device(2).sensor.nsensor = 1;
terrain(1).parcel(1).device(2).sensor.nsensor = 1;
terrain(1).parcel(1).device(2).sensor.type=["Moisture"];
% Outro nó diferente
terrain(1).parcel(2).device(2).transceiver.tipo="lora";
terrain(1).parcel(2).device(2).bateria.tipo = false;
terrain(1).parcel(2).device(2).sensor.type=["Voltage","Current", "Power"];
terrain(1).parcel(2).device(2).sensor.nsensor = 3;

tmp = "[";
for ntrn=1:nterrain
    for nprcl=1:terrain(ntrn).nparcel
        for ndev=1:terrain(ntrn).parcel(nprcl).ndevice
            
            switch(terrain(ntrn).parcel(nprcl).device(ndev).transceiver.tipo)
                case "lora"
                    [terrain(ntrn).parcel(nprcl).device(ndev).transceiver.id,terrain(ntrn).parcel(nprcl).device(ndev).transceiver.json]=create_lora(terrain(ntrn).parcel(nprcl).device(ndev).id);
                    tmp = tmp + terrain(ntrn).parcel(nprcl).device(ndev).transceiver.json + ", ";
                otherwise
                    disp('Sem Transceiver.')
            end
            
            if(terrain(ntrn).parcel(nprcl).device(ndev).bateria.tipo)
                [terrain(ntrn).parcel(nprcl).device(ndev).bateria.id,terrain(ntrn).parcel(nprcl).device(ndev).bateria.json]=create_bateria(terrain(ntrn).parcel(nprcl).device(ndev).id);
                 tmp = tmp + terrain(ntrn).parcel(nprcl).device(ndev).bateria.json + ", ";
            end
            
            % Incluir aqui os sensores e outro hardware
            for nsens=1:terrain(ntrn).parcel(nprcl).device(ndev).sensor.nsensor
                switch terrain(ntrn).parcel(nprcl).device(ndev).sensor.type(nsens)
                    case 'Moisture'
                        [terrain(ntrn).parcel(nprcl).device(ndev).sensor.id(nsens),terrain(ntrn).parcel(nprcl).device(ndev).sensor.json(nsens,:)]=create_moisture(terrain(ntrn).parcel(nprcl).device(ndev).id);
                        tmp = tmp + terrain(ntrn).parcel(nprcl).device(ndev).sensor.json(nsens,:) + ", ";
                    otherwise
                        disp('Em construção');
                end
            end
                    
        end
    end
end

json = char(tmp);
json(end-1) = "]";

% Guarda num ficheiro
fp = fopen('batch_body_device_hardware.json','w');
fprintf(fp,"%s",json);
fclose(fp);
caminho ='/terrain/parcel/device/hardware';
resposta = gera_lote_entidades_no_orion(json,caminho);
response=cria_entidades_http(string(json));
