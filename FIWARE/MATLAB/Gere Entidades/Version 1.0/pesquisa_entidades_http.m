function resposta=pesquisa_entidades_http(refname,refurn)

opt = matlab.net.http.HTTPOptions('ProgressMonitorFcn',@MyProgressMonitor,'UseProgressMonitor',true);

body = [];

%contentTypeField = matlab.net.http.field.ContentTypeField('application/ld+json');
contentTypeField=[];

type1 = matlab.net.http.MediaType('application/ld+json');
acceptField = matlab.net.http.field.AcceptField([type1]);

fiwarefield = matlab.net.http.field.GenericField('Fiware-Service','man4health','Fiware-ServicePath','/terrain/parcel','Link','<https://raw.githubusercontent.com/jpcoelhoATipbDOTpt/MAN4HEALTH/main/DataModel/Context/context-normalized.jsonld>');

header = [acceptField contentTypeField fiwarefield];

% header = matlab.net.http.HeaderField('Content-Type','application/ld+json','Accept','application/ld+json','Fiware-Service','man4health','Fiware-ServicePath','/terrain');

% url="http://localhost:1026/ngsi-ld/v1/entities/urn:ngsi-ld:terrain:ED907CE1";
% url='http://localhost:1026/ngsi-ld/v1/entities?q=refTerrain=="urn:ngsi-ld:terrain:ED907CE1"';
% url="http://localhost:1026/ngsi-ld/v1/entities?q=refTerrain==%22urn%3Angsi-ld%3Aterrain%3AED907CE1%22";
% url="http://localhost:1026/ngsi-ld/v1/entities?q=refTerrain==%22urn:ngsi-ld:terrain:ED907CE1%22"

url="http://localhost:1026/ngsi-ld/v1/entities?q=" + refname + "==%22" + refurn + "%22";
% url=urlencode('http://localhost:1026/ngsi-ld/v1/entities?q=refTerrain=="urn:ngsi-ld:terrain:ED907CE1"')
% obj = matlab.net.URI(url,'refTerrain','urn:ngsi-ld:terrain:ED907CE1')
%url=matlab.net.URI('http://localhost:1026/ngsi-ld/v1/entities?q=refTerrain=="urn:ngsi-ld:terrain:ED907CE1"');


method = matlab.net.http.RequestMethod.GET;
request = matlab.net.http.RequestMessage(method,header,body);

%response = request.send('http://localhost:1026/ngsi-ld/v1/entities?q=refTerrain=="urn:ngsi-ld:terrain:ED907CE1"',opt);
try
    response = request.send(url,opt);
    resposta = jsondecode(string(char(response.Body.Data)'));
catch
    resposta = [];
end

% import matlab.net.http.*
% import matlab.net.http.field.*
% request = RequestMessage( 'POST', ...
%     [ContentTypeField( 'application/ld+json' ), AcceptField('application/ld+json')], ...
%     body );
% response = request.send( 'http://127.0.0.1:1026/ngsi-ld/v1/entities/' );


