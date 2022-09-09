function response=apaga_entidades_batch_http(json,caminho)

% Detalhes sobre operações de CRUD podem ser consultados neste site:
% https://ngsi-ld-tutorials.readthedocs.io/en/latest/ngsi-ld-operations.html
% Em resumo, para criar entidades de forma singular, deve ser feito uma operação POST
% ao seguinte endpoint:
% http://localhost:1026/ngsi-ld/v1/entities/
% Para criar entidades em lote, a operação de POST deve ser drigida ao endpoint:
% http://localhost:1026/ngsi-ld/v1/entityOperations/upsert

opt = matlab.net.http.HTTPOptions('ProgressMonitorFcn',@MyProgressMonitor,'UseProgressMonitor',true);

body = matlab.net.http.MessageBody(json);

contentTypeField = matlab.net.http.field.ContentTypeField('application/ld+json');
type1 = matlab.net.http.MediaType('application/ld+json');
acceptField = matlab.net.http.field.AcceptField([type1]);

fiwarefield = matlab.net.http.field.GenericField('Fiware-Service','man4health','Fiware-ServicePath',caminho);

header = [acceptField contentTypeField fiwarefield];

% header = matlab.net.http.HeaderField('Content-Type','application/ld+json','Accept','application/ld+json','Fiware-Service','man4health','Fiware-ServicePath','/terrain');

method = matlab.net.http.RequestMethod.POST;
request = matlab.net.http.RequestMessage(method,header,body);
response = request.send('http://localhost:1026/ngsi-ld/v1/entityOperations/delete',opt);


% import matlab.net.http.*
% import matlab.net.http.field.*
% request = RequestMessage( 'POST', ...
%     [ContentTypeField( 'application/ld+json' ), AcceptField('application/ld+json')], ...
%     body );
% response = request.send( 'http://127.0.0.1:1026/ngsi-ld/v1/entities/' );


