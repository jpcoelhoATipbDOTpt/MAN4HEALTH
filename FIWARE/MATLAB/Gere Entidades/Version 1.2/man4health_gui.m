function varargout = man4health_gui(varargin)
% MAN4HEALTH_GUI MATLAB code for man4health_gui.fig
%      MAN4HEALTH_GUI, by itself, creates a new MAN4HEALTH_GUI or raises the existing
%      singleton*.
%
%      H = MAN4HEALTH_GUI returns the handle to a new MAN4HEALTH_GUI or the handle to
%      the existing singleton*.
%
%      MAN4HEALTH_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MAN4HEALTH_GUI.M with the given input arguments.
%
%      MAN4HEALTH_GUI('Property','Value',...) creates a new MAN4HEALTH_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before man4health_gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to man4health_gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help man4health_gui

% Last Modified by GUIDE v2.5 17-Sep-2022 12:54:19

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @man4health_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @man4health_gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before man4health_gui is made visible.
function man4health_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to man4health_gui (see VARARGIN)

% Choose default command line output for man4health_gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

resetAllTextBoxes(handles);

% UIWAIT makes man4health_gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = man4health_gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in terrain.
function terrain_Callback(hObject, eventdata, handles)
% hObject    handle to terrain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns terrain contents as cell array
%        contents{get(hObject,'Value')} returns selected item from terrain


% --- Executes during object creation, after setting all properties.
function terrain_CreateFcn(hObject, eventdata, handles)
% hObject    handle to terrain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in load_parcels_from_terrain.
function load_parcels_from_terrain_Callback(hObject, eventdata, handles)
% hObject    handle to load_parcels_from_terrain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.parcel,'String',"");
set(handles.parcel,'Value',1);

set(handles.device,'String',"");
set(handles.device,'Value',1);

set(handles.hardware,'String',"");
set(handles.hardware,'Value',1);

set(handles.nivel_4,'String',"");
set(handles.nivel_4,'Value',1);

set(handles.nivel_3,'String',"");
set(handles.nivel_3,'Value',1);

set(handles.nivel_2,'String',"");
set(handles.nivel_2,'Value',1);

set(handles.nivel_1,'String',"");
set(handles.nivel_1,'Value',1);

set(handles.campos,'String',"");
set(handles.campos,'Value',1);

y=get(handles.terrain,'Value');
x=get(handles.terrain,'String');

host=get(handles.orion_ip_address,'String');

if ~isempty(x)
    urn=x(y,:);
    resposta=pesquisa_entidades_http(host,'refTerrain',urn);
    if ~isempty(resposta)
        set(handles.parcel,'String',[char(resposta.id)]);
    else
        set(handles.parcel,'String',"");
    end
end


% --- Executes on button press in delete_terrain_tree.
function delete_terrain_tree_Callback(hObject, eventdata, handles)
% hObject    handle to delete_terrain_tree (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

y=get(handles.terrain,'Value');
x=get(handles.terrain,'String');
urn=x(y,:);

host=get(handles.orion_ip_address,'String');
delete_tree_terrain(host,urn);

set(handles.parcel,'String',"");
set(handles.parcel,'Value',1);

set(handles.device,'String',"");
set(handles.device,'Value',1);

set(handles.hardware,'String',"");
set(handles.hardware,'Value',1);

set(handles.nivel_4,'String',"");
set(handles.nivel_4,'Value',1);

set(handles.nivel_3,'String',"");
set(handles.nivel_3,'Value',1);

set(handles.nivel_2,'String',"");
set(handles.nivel_2,'Value',1);

set(handles.nivel_1,'String',"");
set(handles.nivel_1,'Value',1);

set(handles.campos,'String',"");
set(handles.campos,'Value',1);


fp=fopen(get(handles.load_terrain,'UserData'),'r');
TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
fclose(fp);

set(handles.terrain,'String',cell2mat(TextAsCells{1}));
set(handles.terrain,'Value',1);



% --- Executes on selection change in parcel.
function parcel_Callback(hObject, eventdata, handles)
% hObject    handle to parcel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns parcel contents as cell array
%        contents{get(hObject,'Value')} returns selected item from parcel


% --- Executes during object creation, after setting all properties.
function parcel_CreateFcn(hObject, eventdata, handles)
% hObject    handle to parcel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% fp=fopen("ParKeys.txt",'r');
% TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
% fclose(fp);
% set(hObject,'String',TextAsCells{1});


% --- Executes on selection change in device.
function device_Callback(hObject, eventdata, handles)
% hObject    handle to device (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns device contents as cell array
%        contents{get(hObject,'Value')} returns selected item from device


% --- Executes during object creation, after setting all properties.
function device_CreateFcn(hObject, eventdata, handles)
% hObject    handle to device (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% fp=fopen("DevKeys.txt",'r');
% TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
% fclose(fp);
% set(hObject,'String',TextAsCells{1});

function hardware_CreateFcn(hObject, eventdata, handles)
% hObject    handle to device (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on button press in load_devices.
function load_devices_Callback(hObject, eventdata, handles)
% hObject    handle to load_devices (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

set(handles.device,'String',"");
set(handles.device,'Value',1);

set(handles.hardware,'String',"");
set(handles.hardware,'Value',1);

set(handles.nivel_4,'String',"");
set(handles.nivel_4,'Value',1);

set(handles.nivel_3,'String',"");
set(handles.nivel_3,'Value',1);

set(handles.nivel_2,'String',"");
set(handles.nivel_2,'Value',1);

set(handles.nivel_1,'String',"");
set(handles.nivel_1,'Value',1);

set(handles.campos,'String',"");
set(handles.campos,'Value',1);

set(handles.device,'Value',1);
y=get(handles.parcel,'Value');
x=get(handles.parcel,'String');
host=get(handles.orion_ip_address,'String');

if~isempty(x)
    urn=x(y,:);
    resposta=pesquisa_entidades_http(host,'refParcel',urn);
    if ~isempty(resposta)
        set(handles.device,'String',[char(resposta.id)]);
    else
        set(handles.device,'String',"");
        set(handles.device,'Value',1);
    end
end

% --- Executes on button press in load_device_hardware.
function load_device_hardware_Callback(hObject, eventdata, handles)
% hObject    handle to load_device_hardware (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

set(handles.hardware,'String',"");
set(handles.hardware,'Value',1);

set(handles.nivel_4,'String',"");
set(handles.nivel_4,'Value',1);

set(handles.nivel_3,'String',"");
set(handles.nivel_3,'Value',1);

set(handles.nivel_2,'String',"");
set(handles.nivel_2,'Value',1);

set(handles.nivel_1,'String',"");
set(handles.nivel_1,'Value',1);

set(handles.campos,'String',"");
set(handles.campos,'Value',1);

y=get(handles.device,'Value');
x=get(handles.device,'String');

host=get(handles.orion_ip_address,'String');

if ~isempty(x)
    urn=x(y,:);
    resposta=pesquisa_entidades_http(host,'refDevice',urn);
    
    if ~isempty(resposta)
        if length(resposta)>1
            for i=1:length(resposta)
                hwr(i)= [string(resposta{i}.id)];
            end
        else
            hwr(1)= [string(resposta.id)];
        end
        set(handles.hardware,'String',hwr);
    else
        set(handles.hardware,'String',"");
        set(handles.hardware,'Value',1);
    end
end

% --- Executes on selection change in group_hardware.
function hardware_Callback(hObject, eventdata, handles)
% hObject    handle to group_hardware (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns group_hardware contents as cell array
%        contents{get(hObject,'Value')} returns selected item from group_hardware


% --- Executes during object creation, after setting all properties.
function group_hardware_CreateFcn(hObject, eventdata, handles)
% hObject    handle to group_hardware (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in hardwareDetail.
function hardwareDetail_Callback(hObject, eventdata, handles)
% hObject    handle to hardwareDetail (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

y=get(handles.hardware,'Value');
x=get(handles.hardware,'String');
host=get(handles.orion_ip_address,'String');

if ~isempty(x)
    if ischar(x)
        urn=x(y,:);
    else
        urn=x{y};
    end
    resposta=atributos_uma_entidade(host,urn);
    set(handles.hardware,'UserData',resposta);
    set(handles.campos,'String',fieldnames(resposta));
    obj=getfield(resposta,"type");
    if strcmp(obj,"LoRa")
        set(handles.lora2gateway,'Visible',true);
    else
        set(handles.lora2gateway,'Visible',false);
    end
end

% if ~isempty(resposta) 
%     set(handles.device,'String',[char(resposta.id)]);
% else
%     set(handles.device,'String',"");
% end


% --- Executes on selection change in campos.
function campos_Callback(hObject, eventdata, handles)
% hObject    handle to campos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns campos contents as cell array
%        contents{get(hObject,'Value')} returns selected item from campos

% Limpa janelas...
set(handles.nivel_3,'String',"");
set(handles.nivel_3,'Value',1);
set(handles.nivel_2,'String',"");
set(handles.nivel_2,'Value',1);
set(handles.nivel_1,'String',"");
set(handles.nivel_1,'Value',1);

resposta = get(handles.hardware,'UserData');
contents = cellstr(get(hObject,'String'));
obj=getfield(resposta,contents{get(hObject,'Value')});
set(handles.campos,'UserData',obj);
if isstruct(obj)
    set(handles.nivel_1,'String',fieldnames(obj));
else
    set(handles.nivel_1,'String',obj);
end

% --- Executes during object creation, after setting all properties.
function campos_CreateFcn(hObject, eventdata, handles)
% hObject    handle to campos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes on selection change in nivel_1.
function nivel_1_Callback(hObject, eventdata, handles)
% hObject    handle to nivel_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns nivel_1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from nivel_1

set(handles.nivel_4,'String',"");
set(handles.nivel_4,'Value',1);
set(handles.nivel_3,'String',"");
set(handles.nivel_3,'Value',1);
set(handles.nivel_2,'String',"");
set(handles.nivel_2,'Value',1);

resposta = get(handles.campos,'UserData');
contents = cellstr(get(hObject,'String'));
if isstruct(resposta)
    obj=getfield(resposta,contents{get(hObject,'Value')});
    isstruct(obj)
    set(handles.nivel_1,'UserData',obj);
    if isstruct(obj)
        set(handles.nivel_2,'String',fieldnames(obj));
    else
        set(handles.nivel_2,'String',obj);
    end
end



% --- Executes during object creation, after setting all properties.
function nivel_1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to nivel_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in nivel_2.
function nivel_2_Callback(hObject, eventdata, handles)
% hObject    handle to nivel_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns nivel_2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from nivel_2

set(handles.nivel_4,'String',"");
set(handles.nivel_4,'Value',1);
set(handles.nivel_3,'String',"");
set(handles.nivel_3,'Value',1);

resposta = get(handles.nivel_1,'UserData');
contents = cellstr(get(hObject,'String'));
if isstruct(resposta)
    obj=getfield(resposta,contents{get(hObject,'Value')});
    isstruct(obj)
    set(handles.nivel_2,'UserData',obj);
    if isstruct(obj)
        set(handles.nivel_3,'String',fieldnames(obj));
    else
        set(handles.nivel_3,'String',obj);
    end
end


% --- Executes during object creation, after setting all properties.
function nivel_2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to nivel_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in nivel_3.
function nivel_3_Callback(hObject, eventdata, handles)
% hObject    handle to nivel_3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns nivel_3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from nivel_3

set(handles.nivel_4,'String',"");
set(handles.nivel_4,'Value',1);

resposta = get(handles.nivel_2,'UserData');
contents = cellstr(get(hObject,'String'));
if isstruct(resposta)
    obj=getfield(resposta,contents{get(hObject,'Value')});
    isstruct(obj)
    set(handles.nivel_3,'UserData',obj);
    if isstruct(obj)
        set(handles.nivel_4,'String',fieldnames(obj));
    else
        set(handles.nivel_4,'String',obj);
    end
end

% --- Executes during object creation, after setting all properties.
function nivel_3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to nivel_3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in delete_device_tree.
function delete_device_tree_Callback(hObject, eventdata, handles)
% hObject    handle to delete_device_tree (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Come�a por determinar quais os urn associados a esse terreno


% --- Executes on button press in delete_parcel_tree.
function delete_parcel_tree_Callback(hObject, eventdata, handles)
% hObject    handle to delete_parcel_tree (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on selection change in nivel_4.
function nivel_4_Callback(hObject, eventdata, handles)
% hObject    handle to nivel_4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns nivel_4 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from nivel_4


% --- Executes during object creation, after setting all properties.
function nivel_4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to nivel_4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in purgeall.
function purgeall_Callback(hObject, eventdata, handles)
% hObject    handle to purgeall (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

fp=fopen(get(handles.load_terrain,'UserData'),'r');
TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
fclose(fp);
[n_terrain,~]=size(TextAsCells{1});

host=get(handles.orion_ip_address,'String');

for nter=1:n_terrain
    delete_tree_terrain(host,TextAsCells{1}{nter});
end

resetAllTextBoxes(handles)
    


% --- Executes on button press in load_terrain.
function load_terrain_Callback(hObject, eventdata, handles)
% hObject    handle to load_terrain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[filename, pathname] = uigetfile('*.txt', 'Selecione o ficheiro com os urn dos terrenos');
if isequal(filename,0) || isequal(pathname,0)
    fp=-1;
else
    fp=fopen(fullfile(pathname, filename),'r');
end

if fp==-1
    err=errordlg('Ficheiro TerID.txt n�o encontrado.', 'Erro:', 'modal');
    uiwait(err);
    resetAllTextBoxes(handles)
    return
else
    TextAsCells = textscan(fp, '%s', 'Delimiter', '\n');
    fclose(fp);
    set(handles.terrain,'String',cell2mat(TextAsCells{1}));
    set(hObject,'UserData',fullfile(pathname, filename));
end

function resetAllTextBoxes(handles)

set(handles.terrain,'String',"");
set(handles.terrain,'Value',1);

set(handles.parcel,'String',"");
set(handles.parcel,'Value',1);

set(handles.device,'String',"");
set(handles.device,'Value',1);

set(handles.hardware,'String',"");
set(handles.hardware,'Value',1);

set(handles.nivel_4,'String',"");
set(handles.nivel_4,'Value',1);

set(handles.nivel_3,'String',"");
set(handles.nivel_3,'Value',1);

set(handles.nivel_2,'String',"");
set(handles.nivel_2,'Value',1);

set(handles.nivel_1,'String',"");
set(handles.nivel_1,'Value',1);

set(handles.campos,'String',"");
set(handles.campos,'Value',1);



function orion_ip_address_Callback(hObject, eventdata, handles)
% hObject    handle to orion_ip_address (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of orion_ip_address as text
%        str2double(get(hObject,'String')) returns contents of orion_ip_address as a double

host=get(handles.orion_ip_address,'String');
url="http://" + host + ":1026/version";
method = matlab.net.http.RequestMethod.GET;
request = matlab.net.http.RequestMessage(method,[],[]);
set(handles.wait,'Visible',true);
drawnow;
try
    response = request.send(url,[]);
    err=warndlg('Orion IP Address changed.', 'Warning', 'modal');
    uiwait(err);
catch
    err=errordlg('Invalid Orion IP Address', 'Error', 'modal');
    uiwait(err);
end
set(handles.wait,'Visible',false);



% --- Executes during object creation, after setting all properties.
function orion_ip_address_CreateFcn(hObject, eventdata, handles)
% hObject    handle to orion_ip_address (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in lora2gateway.
function lora2gateway_Callback(hObject, eventdata, handles)
% hObject    handle to lora2gateway (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Verifica se o tipo � LoRa

resposta = get(handles.hardware,'UserData')

NwkSkey=parse(resposta.NwkSkey.value)
AppSKey=parse(resposta.AppSkey.value)
DevAddr=parse(resposta.DevAddr.value)
set(handles.nivel_3,'String',["Network Session Key:", "APP Session Key:","Dev ADDR:"])
set(handles.nivel_4,'String',{NwkSkey,AppSKey,DevAddr})
