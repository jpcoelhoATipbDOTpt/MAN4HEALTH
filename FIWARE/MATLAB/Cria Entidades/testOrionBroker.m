function result = testOrionBroker(url)

method = matlab.net.http.RequestMethod.GET;
req = matlab.net.http.RequestMessage(method,[],[]);
try  
    req.send(url);
    result=true;
catch
    result=false;
end
