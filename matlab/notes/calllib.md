https://github.com/pkmital/eegLogger/blob/master/include/edk.h

https://www.mathworks.com/help/matlab/ref/calllib.html

[EmotivEEG data in Excel](https://www.mathworks.com/matlabcentral/answers/319229-emotiveeg-data-in-excel)

```matlab
classdef EmotivEEG < handle
    %----------
    %EmotivEEG 
    %----------
    %queries the EDK library in order to recieve data from the
    %Emotiv EEG headset
    %
    %%Usage;
    % To create the object
    % a = EmotivEEG;
    % % To start a timmer (keeps running until stopped) and get latest data
    % a.Run
    % % To plot the latest /c data variable values
    % a.Plot
    % % To stop the timmer
    % a.Stop
    % % To record 10 seconds of data and save to a file
    % a.Record(10)    
    % % To load recorded data from file into /c data variable (NOTE if you have a timer on this will be overwritten)
    % LoadRecordedData(self,filename)    
    % % To disconnect and unload the library
    % delete(a)

      properties
          sampFreq = 128;                   
          recordSeconds = 1;        
          acqisitionSeconds = 1;
          timerPeriod = 0.35; %seconds *MUST BE LESS THAN acqisitionSeconds. Also used for updating the record data
          plotTimerPeriod = 0.5;
          fig_h;
          showDebug = false;
      end

      properties (Constant)
          unitIdentifier = 'Emotiv Systems-5'        
      end

      properties (SetAccess = protected)
          runAsyncTimer
          plotTimer
          channelCount
          data = [];
          eEvent
          dataRowCount
          hData % handles (pointer) to the data stored in library
          DataChannels
          EE_DataChannels_enum = struct('ED_COUNTER',0,'ED_INTERPOLATED',1,'ED_RAW_CQ',2,'ED_AF3',3,'ED_F7',4,'ED_F3',5,'ED_FC5',6,'ED_T7',7,'ED_P7',8,'ED_O1',9,'ED_O2',10,'ED_P8',11,'ED_T8',12,'ED_FC6',13,'ED_F4',14,'ED_F8',15,'ED_AF4',16,'ED_GYROX',17,'ED_GYROY',18,'ED_TIMESTAMP',19,'ED_ES_TIMESTAMP',20,'ED_FUNC_ID',21,'ED_FUNC_VALUE',22,'ED_MARKER',23,'ED_SYNC_SIGNAL',24);
          EE_CognitivTrainingControl_enum = struct('COG_NONE',0,'COG_START',1,'COG_ACCEPT',2,'COG_REJECT',3,'COG_ERASE',4,'COG_RESET',5);
          EE_ExpressivAlgo_enum = struct('EXP_NEUTRAL',1,'EXP_BLINK',2,'EXP_WINK_LEFT',4,'EXP_WINK_RIGHT',8,'EXP_HORIEYE',16,'EXP_EYEBROW',32,'EXP_FURROW',64,'EXP_SMILE',128,'EXP_CLENCH',256,'EXP_LAUGH',512,'EXP_SMIRK_LEFT',1024,'EXP_SMIRK_RIGHT',2048);
          EE_ExpressivTrainingControl_enum = struct('EXP_NONE',0,'EXP_START',1,'EXP_ACCEPT',2,'EXP_REJECT',3,'EXP_ERASE',4,'EXP_RESET',5);
          EE_ExpressivThreshold_enum = struct('EXP_SENSITIVITY',0);
          EE_CognitivEvent_enum = struct('EE_CognitivNoEvent',0,'EE_CognitivTrainingStarted',1,'EE_CognitivTrainingSucceeded',2,'EE_CognitivTrainingFailed',3,'EE_CognitivTrainingCompleted',4,'EE_CognitivTrainingDataErased',5,'EE_CognitivTrainingRejected',6,'EE_CognitivTrainingReset',7,'EE_CognitivAutoSamplingNeutralCompleted',8,'EE_CognitivSignatureUpdated',9);
          EE_EmotivSuite_enum=struct('EE_EXPRESSIV',0,'EE_AFFECTIV',1,'EE_COGNITIV',2);
          EE_ExpressivEvent_enum=struct('EE_ExpressivNoEvent',0,'EE_ExpressivTrainingStarted',1,'EE_ExpressivTrainingSucceeded',2,'EE_ExpressivTrainingFailed',3,'EE_ExpressivTrainingCompleted',4,'EE_ExpressivTrainingDataErased',5,'EE_ExpressivTrainingRejected',6,'EE_ExpressivTrainingReset',7);
          EE_CognitivAction_enum=struct('COG_NEUTRAL',1,'COG_PUSH',2,'COG_PULL',4,'COG_LIFT',8,'COG_DROP',16,'COG_LEFT',32,'COG_RIGHT',64,'COG_ROTATE_LEFT',128,'COG_ROTATE_RIGHT',256,'COG_ROTATE_CLOCKWISE',512,'COG_ROTATE_COUNTER_CLOCKWISE',1024,'COG_ROTATE_FORWARDS',2048,'COG_ROTATE_REVERSE',4096,'COG_DISAPPEAR',8192);
          EE_InputChannels_enum=struct('EE_CHAN_CMS',0,'EE_CHAN_DRL',1,'EE_CHAN_FP1',2,'EE_CHAN_AF3',3,'EE_CHAN_F7',4,'EE_CHAN_F3',5,'EE_CHAN_FC5',6,'EE_CHAN_T7',7,'EE_CHAN_P7',8,'EE_CHAN_O1',9,'EE_CHAN_O2',10,'EE_CHAN_P8',11,'EE_CHAN_T8',12,'EE_CHAN_FC6',13,'EE_CHAN_F4',14,'EE_CHAN_F8',15,'EE_CHAN_AF4',16,'EE_CHAN_FP2',17);
          EE_ExpressivSignature_enum=struct('EXP_SIG_UNIVERSAL',0,'EXP_SIG_TRAINED',1);
          EE_Event_enum=struct('EE_UnknownEvent',0,'EE_EmulatorError',1,'EE_ReservedEvent',2,'EE_UserAdded',16,'EE_UserRemoved',32,'EE_EmoStateUpdated',64,'EE_ProfileEvent',128,'EE_CognitivEvent',256,'EE_ExpressivEvent',512,'EE_InternalStateChanged',1024,'EE_AllEvent',2032);
          DataChannelsNames = {'ED_COUNTER','ED_INTERPOLATED','ED_RAW_CQ','ED_AF3','ED_F7','ED_F3','ED_FC5','ED_T7','ED_P7','ED_O1','ED_O2','ED_P8','ED_T8','ED_FC6','ED_F4','ED_F8','ED_AF4','ED_GYROX','ED_GYROY','ED_TIMESTAMP','ED_ES_TIMESTAMP','ED_FUNC_ID','ED_FUNC_VALUE','ED_MARKER','ED_SYNC_SIGNAL'};
      end

      properties (Access = protected)
          tempData = [] % holds the data while it is being read from the library
      end

      methods
          function self = EmotivEEG()
              self.DataChannels = self.EE_DataChannels_enum; % THIS MAY BE REDUNDANT
              self.channelCount = length(self.DataChannelsNames);

              % Check to see if library was already loaded
              if ~libisloaded('edk')    
                  [notfound,warnings] = loadlibrary('edk.dll','edk.h');                 %#ok<NASGU,ASGLU>
                  disp('EDK library loaded');
              else
                  disp('EDK library already loaded');
              end

               % Success if value returned is 0 
              if calllib('edk','EE_EngineConnect',int8([self.unitIdentifier 0]))
                  error(['An error occured when using EE_EngineConnect to connect to ',self.unitIdentifier])
              else
                  disp(['Successfully connected to ',self.unitIdentifier])
              end

              % Create a data pointer
              self.hData = calllib('edk','EE_DataCreate');
              % Set the record time buffer size
              calllib('edk','EE_DataSetBufferSizeInSec',self.acqisitionSeconds);
              % Create an events engine
              self.eEvent = calllib('edk','EE_EmoEngineEventCreate');

              self.dataRowCount = self.acqisitionSeconds * self.sampFreq;
              self.data = zeros(self.dataRowCount,self.channelCount);
              self.tempData = self.data; % requierd to work on the data variable but still allow external access to data            
              pause(1);
          end

%%delete        
        function delete(self)
            self.Stop()
            self.StopPlot()

              if calllib('edk','EE_EngineDisconnect')
                  warning(['Some error disconnecting from ',self.unitIdentifier]) %#ok<WNTAG>
              else
                  disp(['Successfully disconnected from ',self.unitIdentifier])
              end            
              pause(0.1);
              unloadlibrary('edk');            
          end

%%Run
% Start a timer to continuously update the state of the data variable every
% /c timerPeriod
        function Run(self)
            self.runAsyncTimer = timer('TimerFcn', @(src,event)UpdateData(self), 'name', 'RunAsync','Period', self.timerPeriod,'BusyMode','drop','ExecutionMode','fixedDelay');
            start(self.runAsyncTimer); 
            pause(1);
        end

          function Stop(self)
              if ~isempty(self.runAsyncTimer) && strcmp(self.runAsyncTimer.Running,'on')
                  stop(self.runAsyncTimer);
              end
          end

%%Plot
% Starts a plot timer to keep updating a figure
        function Plot(self)        
            if isempty(self.runAsyncTimer) || strcmp(self.runAsyncTimer.Running,'off')
                warning('The update data timer is not currently started. Please start if you want to see new data.') %#ok<WNTAG>                
            end
            self.plotTimer = timer('TimerFcn', @(src,event)UpdatePlot(self), 'name', 'UpdatePlotTimer','Period', self.plotTimerPeriod,'BusyMode','drop','ExecutionMode','fixedDelay');
            start(self.plotTimer);
        end

% Stops the plot timer
        function StopPlot(self)
            if ~isempty(self.plotTimer) && strcmp(self.plotTimer.Running,'on')
                stop(self.plotTimer);
            end
        end

% The update plot function, which should be changed to show what needs to be shown        
        function UpdatePlot(self)
            if isempty(self.fig_h)
                self.fig_h = figure;
            end
            set(0,'CurrentFigure',self.fig_h)
            surf(self.data);
        end

%%Record data
% This will block until there is recordSeconds worth of new data then it
% will save this to file (as .mat)
        function recordFilename = Record(self,recordSeconds_local)
            if ~isempty(self.runAsyncTimer) && strcmp(self.runAsyncTimer.Running,'on')
                warning('You should not run the timer and record simultaneously. Stopping the timmer') %#ok<WNTAG>
                self.Stop()
            end

              if nargin < 2
                  recordSeconds_local = self.recordSeconds;
              end

              starttime = clock;
              originalDesiredSampleCount = recordSeconds_local * self.sampFreq;
              remainingDesiredSampleCount = originalDesiredSampleCount;

              recordData = zeros(recordSeconds_local * self.sampFreq, self.channelCount);
              currentIndex = 1;
              while remainingDesiredSampleCount > 0 
                  % Make sure it breaks out in 2* the correct time even if the number of samples is not there
                  if etime(clock,starttime) > 2 * recordSeconds_local
                      break;
                  end
                  nSamplesTaken = UpdateData(self);
                  if nSamplesTaken == 0 
                      continue;
                  end
                  % Note that this matrix WILL PROBABLY be bigger than the desiredSampleCount 
                  overShoot = currentIndex + nSamplesTaken - originalDesiredSampleCount;
                  if overShoot <= 0
                      recordData(currentIndex:currentIndex+nSamplesTaken-1,:) = self.data(1:nSamplesTaken,:);                    
                      remainingDesiredSampleCount = remainingDesiredSampleCount - nSamplesTaken;
                  else
                      recordData(currentIndex:originalDesiredSampleCount,:) = self.data(overShoot:nSamplesTaken,:);                    
                      remainingDesiredSampleCount = 0;
                  end

                  currentIndex = currentIndex + nSamplesTaken;                

                  disp(['Recording... recieved  ,',num2str(currentIndex + 1), ' samples so far in' ,num2str(etime(clock,starttime)),' secs. Still waiting for ', num2str(remainingDesiredSampleCount),' of ', num2str(originalDesiredSampleCount),' samples']);
                  pause(self.timerPeriod);
              end
              recordFilename = ['EEGlog',datestr(now,30),'.mat'];
              save(recordFilename,'recordData');
              disp(['Recording complete. Saved to ',recordFilename]);
          end

%%LoadRecordedData
        function LoadRecordedData(self,filename)
            if ~isempty(self.runAsyncTimer) && strcmp(self.runAsyncTimer.Running,'on')
                warning('You should not run the timer and load record data simultaneously (else it will overwrite it). I''m stopping the timmer') %#ok<WNTAG>
                self.Stop()
            end
            temp = load(filename);
            self.data = temp.recordData;
        end

%%UpdateData 
% Update the data matrix by pushing old values on and adding new values at
% the front
        function nSamplesTaken = UpdateData(self)
            state = calllib('edk','EE_EngineGetNextEvent',self.eEvent); 
            if state~=0 % state = 0 if everything's OK
                warning('Everything is NOT OK: Is the headset connected, turned on, and on someone''s head?'); %#ok<WNTAG>
            end

              eventType = calllib('edk','EE_EmoEngineEventGetType',self.eEvent);
              %disp(eventType);
              userID=libpointer('uint32Ptr',0);
              calllib('edk','EE_EmoEngineEventGetUserId',self.eEvent, userID);

              if strcmp(eventType,'EE_UserAdded') == true
                  userID_value = get(userID,'value');
                  calllib('edk','EE_DataAcquisitionEnable',userID_value,true);
              end

              calllib('edk','EE_DataUpdateHandle', 0, self.hData);
              nSamples = libpointer('uint32Ptr',0);
              calllib('edk','EE_DataGetNumberOfSample', self.hData, nSamples);

              nSamplesTaken = get(nSamples,'value') ;
              if (nSamplesTaken ~= 0)
                  % Should check this and only get data if full amount is  available and new 
                  % (it is required for the get call to know how big dataPtr is)
                  if self.showDebug  
                      disp(['nSamplesTaken = ',num2str(nSamplesTaken)])
                  end

                  % Assign memory for the number (in lib) for samples taken on a single channel
                  channelDataPtr = libpointer('doublePtr',zeros(1,nSamplesTaken));

                  % Push the old values of the end, move newest ones to end
                  self.tempData = [zeros(nSamplesTaken,self.channelCount) ...
                                  ;self.data(1:self.dataRowCount-nSamplesTaken,:)];

                  % Go through each of the channels and get all the samples for that channel
                  for i = 1:length(fieldnames(self.EE_DataChannels_enum))
                      calllib('edk','EE_DataGet',self.hData, self.DataChannels.([self.DataChannelsNames{i}]), channelDataPtr, uint32(nSamplesTaken));
                      channelData = get(channelDataPtr,'value');
                      % Fill in our matrix of the latest data                    
                      self.tempData(1:nSamplesTaken,i) = channelData;

                      if (nSamplesTaken~=length(channelData))
                          warning('The nSamplesTaken shoul == length(channelData), Ask Gavin'); %#ok<WNTAG>
                      end
                  end

                  % Required so data variable is safely available externally to work with,
                  % Only update the data once the samples from the most recent read operation have been added
                  self.data = self.tempData;
              end 
          end
      end
  end
```

[New Emotive doesn't capture the data correctly](https://www.mathworks.com/matlabcentral/answers/350635-new-emotive-doesn-t-capture-the-data-correctly)

```matlab
classdef EmotivEEG < handle
    %----------
    %EmotivEEG 
    %----------
    %queries the EDK library in order to recieve data from the
    %Emotiv EEG headset
    %
    %%Usage;
    % To create the object
    % a = EmotivEEG;
    % % To start a timmer (keeps running until stopped) and get latest data
    % a.Run
    % % To plot the latest /c data variable values
    % a.Plot
    % % To stop the timmer
    % a.Stop
    % % To record 10 seconds of data and save to a file
    % a.Record(10)    
    % % To load recorded data from file into /c data variable (NOTE if you have a timer on this will be overwritten)
    % LoadRecordedData(self,filename)    
    % % To disconnect and unload the library
    % delete(a)

      properties
          sampFreq = 128;
          recordSeconds = 1;        
          acqisitionSeconds = 1; %If use_new_update==false set this to the max possible duration
          timerPeriod = 0.35; %seconds *MUST BE LESS THAN acqisitionSeconds. Also used for updating the record data
          plotTimerPeriod = 0.5;
          fig_h;
          showDebug = false;
          use_new_update = true;
      end

      properties (Constant)
          unitIdentifier = 'Emotiv Systems-5'        
      end

      properties (SetAccess = protected)
          runAsyncTimer
          plotTimer
          channelCount
          data = [];
          eEvent
          dataRowCount
          hData % handles (pointer) to the data stored in library
          DataChannels
          EE_DataChannels_enum = struct('ED_COUNTER',0,'ED_INTERPOLATED',1,'ED_RAW_CQ',2,'ED_AF3',3,'ED_F7',4,'ED_F3',5,'ED_FC5',6,'ED_T7',7,'ED_P7',8,'ED_O1',9,'ED_O2',10,'ED_P8',11,'ED_T8',12,'ED_FC6',13,'ED_F4',14,'ED_F8',15,'ED_AF4',16,'ED_GYROX',17,'ED_GYROY',18,'ED_TIMESTAMP',19,'ED_ES_TIMESTAMP',20,'ED_FUNC_ID',21,'ED_FUNC_VALUE',22,'ED_MARKER',23,'ED_SYNC_SIGNAL',24);
          EE_CognitivTrainingControl_enum = struct('COG_NONE',0,'COG_START',1,'COG_ACCEPT',2,'COG_REJECT',3,'COG_ERASE',4,'COG_RESET',5);
          EE_ExpressivAlgo_enum = struct('EXP_NEUTRAL',1,'EXP_BLINK',2,'EXP_WINK_LEFT',4,'EXP_WINK_RIGHT',8,'EXP_HORIEYE',16,'EXP_EYEBROW',32,'EXP_FURROW',64,'EXP_SMILE',128,'EXP_CLENCH',256,'EXP_LAUGH',512,'EXP_SMIRK_LEFT',1024,'EXP_SMIRK_RIGHT',2048);
          EE_ExpressivTrainingControl_enum = struct('EXP_NONE',0,'EXP_START',1,'EXP_ACCEPT',2,'EXP_REJECT',3,'EXP_ERASE',4,'EXP_RESET',5);
          EE_ExpressivThreshold_enum = struct('EXP_SENSITIVITY',0);
          EE_CognitivEvent_enum = struct('EE_CognitivNoEvent',0,'EE_CognitivTrainingStarted',1,'EE_CognitivTrainingSucceeded',2,'EE_CognitivTrainingFailed',3,'EE_CognitivTrainingCompleted',4,'EE_CognitivTrainingDataErased',5,'EE_CognitivTrainingRejected',6,'EE_CognitivTrainingReset',7,'EE_CognitivAutoSamplingNeutralCompleted',8,'EE_CognitivSignatureUpdated',9);
          EE_EmotivSuite_enum=struct('EE_EXPRESSIV',0,'EE_AFFECTIV',1,'EE_COGNITIV',2);
          EE_ExpressivEvent_enum=struct('EE_ExpressivNoEvent',0,'EE_ExpressivTrainingStarted',1,'EE_ExpressivTrainingSucceeded',2,'EE_ExpressivTrainingFailed',3,'EE_ExpressivTrainingCompleted',4,'EE_ExpressivTrainingDataErased',5,'EE_ExpressivTrainingRejected',6,'EE_ExpressivTrainingReset',7);
          EE_CognitivAction_enum=struct('COG_NEUTRAL',1,'COG_PUSH',2,'COG_PULL',4,'COG_LIFT',8,'COG_DROP',16,'COG_LEFT',32,'COG_RIGHT',64,'COG_ROTATE_LEFT',128,'COG_ROTATE_RIGHT',256,'COG_ROTATE_CLOCKWISE',512,'COG_ROTATE_COUNTER_CLOCKWISE',1024,'COG_ROTATE_FORWARDS',2048,'COG_ROTATE_REVERSE',4096,'COG_DISAPPEAR',8192);
          EE_InputChannels_enum=struct('EE_CHAN_CMS',0,'EE_CHAN_DRL',1,'EE_CHAN_FP1',2,'EE_CHAN_AF3',3,'EE_CHAN_F7',4,'EE_CHAN_F3',5,'EE_CHAN_FC5',6,'EE_CHAN_T7',7,'EE_CHAN_P7',8,'EE_CHAN_O1',9,'EE_CHAN_O2',10,'EE_CHAN_P8',11,'EE_CHAN_T8',12,'EE_CHAN_FC6',13,'EE_CHAN_F4',14,'EE_CHAN_F8',15,'EE_CHAN_AF4',16,'EE_CHAN_FP2',17);
          EE_ExpressivSignature_enum=struct('EXP_SIG_UNIVERSAL',0,'EXP_SIG_TRAINED',1);
          EE_Event_enum=struct('EE_UnknownEvent',0,'EE_EmulatorError',1,'EE_ReservedEvent',2,'EE_UserAdded',16,'EE_UserRemoved',32,'EE_EmoStateUpdated',64,'EE_ProfileEvent',128,'EE_CognitivEvent',256,'EE_ExpressivEvent',512,'EE_InternalStateChanged',1024,'EE_AllEvent',2032);
          DataChannelsNames = {'ED_COUNTER','ED_INTERPOLATED','ED_RAW_CQ','ED_AF3','ED_F7','ED_F3','ED_FC5','ED_T7','ED_P7','ED_O1','ED_O2','ED_P8','ED_T8','ED_FC6','ED_F4','ED_F8','ED_AF4','ED_GYROX','ED_GYROY','ED_TIMESTAMP','ED_ES_TIMESTAMP','ED_FUNC_ID','ED_FUNC_VALUE','ED_MARKER','ED_SYNC_SIGNAL'};
      end

      properties (Access = protected)
          tempData = [] % holds the data while it is being read from the library
      end

      methods
          function self = EmotivEEG()
              self.DataChannels = self.EE_DataChannels_enum; % THIS MAY BE REDUNDANT
              self.channelCount = length(self.DataChannelsNames);

              % Check to see if library was already loaded
              if ~libisloaded('edk')    
                  [notfound,warnings] = loadlibrary('edk.dll','edk.h');                 %#ok<NASGU,ASGLU>
                  disp('EDK library loaded');
              else
                  disp('EDK library already loaded');
              end

               % Success if value returned is 0 
              if calllib('edk','EE_EngineConnect',self.unitIdentifier)
                  error(['An error occured when using EE_EngineConnect to connect to ',self.unitIdentifier])
              else
                  disp(['Successfully connected to ',self.unitIdentifier])
              end

              % Create a data pointer
              self.hData = calllib('edk','EE_DataCreate');
              % Set the record time buffer size
              calllib('edk','EE_DataSetBufferSizeInSec',self.acqisitionSeconds);
              % Create an events engine
              self.eEvent = calllib('edk','EE_EmoEngineEventCreate');

              self.dataRowCount = self.acqisitionSeconds * self.sampFreq;
              if(self.use_new_update==true)
                  self.data = [];
              else
                  self.data = zeros(self.dataRowCount,self.channelCount);
              end
              self.tempData = self.data; % requierd to work on the data variable but still allow external access to data            
              pause(1);
          end

%%delete        
        function delete(self)
            self.Stop()
            self.StopPlot()

              if calllib('edk','EE_EngineDisconnect')
                  warning(['Some error disconnecting from ',self.unitIdentifier]) %#ok<WNTAG>
              else
                  disp(['Successfully disconnected from ',self.unitIdentifier])
              end            
              pause(0.1);
              unloadlibrary('edk');            
          end

%%Run
% Start a timer to continuously update the state of the data variable every
% /c timerPeriod
        function Run(self)
            if(self.use_new_update==false)
                self.runAsyncTimer = timer('TimerFcn', @(src,event)UpdateData(self), 'name', 'RunAsync','Period', self.timerPeriod,'BusyMode','drop','ExecutionMode','fixedDelay');
            else
                self.runAsyncTimer = timer('TimerFcn', @(src,event)UpdateDataNEW(self), 'name', 'RunAsync','Period', self.timerPeriod,'BusyMode','drop','ExecutionMode','fixedDelay');
            end
            start(self.runAsyncTimer); 
            pause(1);
        end

          function Stop(self)
              if ~isempty(self.runAsyncTimer) && strcmp(self.runAsyncTimer.Running,'on')
                  stop(self.runAsyncTimer);
              end
          end

%%Plot
% Starts a plot timer to keep updating a figure
        function Plot(self)        
            if isempty(self.runAsyncTimer) || strcmp(self.runAsyncTimer.Running,'off')
                warning('The update data timer is not currently started. Please start if you want to see new data.') %#ok<WNTAG>                
            end
            self.plotTimer = timer('TimerFcn', @(src,event)UpdatePlot(self), 'name', 'UpdatePlotTimer','Period', self.plotTimerPeriod,'BusyMode','drop','ExecutionMode','fixedDelay');
            start(self.plotTimer);
        end

% Stops the plot timer
        function StopPlot(self)
            if ~isempty(self.plotTimer) && strcmp(self.plotTimer.Running,'on')
                stop(self.plotTimer);
            end
        end

% The update plot function, which should be changed to show what needs to be shown        
        function UpdatePlot(self)
            if isempty(self.fig_h)
                self.fig_h = figure;
            end
            set(0,'CurrentFigure',self.fig_h)
            surf(self.data);
        end

%%Record data
% This will block until there is recordSeconds worth of new data then it
% will save this to file (as .mat)
        function recordFilename = Record(self,recordSeconds_local)
            if ~isempty(self.runAsyncTimer) && strcmp(self.runAsyncTimer.Running,'on')
                warning('You should not run the timer and record simultaneously. Stopping the timer') %#ok<WNTAG>
                self.Stop()
            end

              if nargin < 2
                  recordSeconds_local = self.recordSeconds;
              end

              starttime = clock;
              originalDesiredSampleCount = recordSeconds_local * self.sampFreq;
              remainingDesiredSampleCount = originalDesiredSampleCount;

              recordData = zeros(recordSeconds_local * self.sampFreq, self.channelCount);
              currentIndex = 1;
              while remainingDesiredSampleCount > 0 
                  % Make sure it breaks out in 2* the correct time even if the number of samples is not there
                  if etime(clock,starttime) > 2 * recordSeconds_local
                      break;
                  end
                  nSamplesTaken = UpdateData(self);
                  if nSamplesTaken == 0 
                      continue;
                  end
                  % Note that this matrix WILL PROBABLY be bigger than the desiredSampleCount 
                  overShoot = currentIndex + nSamplesTaken - originalDesiredSampleCount;
                  if overShoot <= 0
                      recordData(currentIndex:currentIndex+nSamplesTaken-1,:) = self.data(1:nSamplesTaken,:);                    
                      remainingDesiredSampleCount = remainingDesiredSampleCount - nSamplesTaken;
                  else
                      recordData(currentIndex:originalDesiredSampleCount,:) = self.data(overShoot:nSamplesTaken,:);                    
                      remainingDesiredSampleCount = 0;
                  end

                  currentIndex = currentIndex + nSamplesTaken;                

                  disp(['Recording... recieved  , ',num2str(currentIndex + 1), ' samples so far in' ,num2str(etime(clock,starttime)),' secs. Still waiting for ', num2str(remainingDesiredSampleCount),' of ', num2str(originalDesiredSampleCount),' samples']);
                  pause(self.timerPeriod);
              end
              recordFilename = ['EEGlog',datestr(now,30),'.mat'];
              save(recordFilename,'recordData');
              disp(['Recording complete. Saved to ',recordFilename]);
          end

%%LoadRecordedData
        function LoadRecordedData(self,filename)
            if ~isempty(self.runAsyncTimer) && strcmp(self.runAsyncTimer.Running,'on')
                warning('You should not run the timer and load record data simultaneously (else it will overwrite it). I''m stopping the timmer') %#ok<WNTAG>
                self.Stop()
            end
            temp = load(filename);
            self.data = temp.recordData;
        end

%%UpdateData 
% Update the data matrix by pushing old values on and adding new values at
% the front
        function nSamplesTaken = UpdateData(self)
            state = calllib('edk','EE_EngineGetNextEvent',self.eEvent); 
            if state~=0 % state = 0 if everything's OK
                warning('Everything is NOT OK: Is the headset connected, turned on, and on someone''s head?'); %#ok<WNTAG>
            end

              eventType = calllib('edk','EE_EmoEngineEventGetType',self.eEvent);
              %disp(eventType);
              userID=libpointer('uint32Ptr',0);
              calllib('edk','EE_EmoEngineEventGetUserId',self.eEvent, userID);

              if strcmp(eventType,'EE_UserAdded') == true
                  userID_value = get(userID,'value');
                  calllib('edk','EE_DataAcquisitionEnable',userID_value,true);
              end

              calllib('edk','EE_DataUpdateHandle', 0, self.hData);
              nSamples = libpointer('uint32Ptr',0);
              calllib('edk','EE_DataGetNumberOfSample', self.hData, nSamples);

              nSamplesTaken = get(nSamples,'value') ;
              if (nSamplesTaken ~= 0)
                  % Should check this and only get data if full amount is  available and new 
                  % (it is required for the get call to know how big dataPtr is)
                  if self.showDebug  
                      disp(['nSamplesTaken = ',num2str(nSamplesTaken)])
                  end

                  % Assign memory for the number (in lib) for samples taken on a single channel
                  channelDataPtr = libpointer('doublePtr',zeros(1,nSamplesTaken));

                  % Push the old values of the end, move newest ones to end
                  self.tempData = [zeros(nSamplesTaken,self.channelCount) ...
                                  ;self.data(1:self.dataRowCount-nSamplesTaken,:)];

                  % Go through each of the channels and get all the samples for that channel
                  for i = 1:length(fieldnames(self.EE_DataChannels_enum))
                      calllib('edk','EE_DataGet',self.hData, self.DataChannels.([self.DataChannelsNames{i}]), channelDataPtr, uint32(nSamplesTaken));
                      channelData = get(channelDataPtr,'value');
                      % Fill in our matrix of the latest data                    
                      self.tempData(1:nSamplesTaken,i) = channelData;

                      if (nSamplesTaken~=length(channelData))
                          warning('The nSamplesTaken shoul == length(channelData), Ask Gavin'); %#ok<WNTAG>
                      end
                  end

                  % Required so data variable is safely available externally to work with,
                  % Only update the data once the samples from the most recent read operation have been added
                  self.data = self.tempData;
  %                 self.data = [self.data; self.tempData];
              end
          end    
  %%UpdateData 
  % Update the data matrix by pushing old values on and adding new values at
  % the front
          function nSamplesTaken = UpdateDataNEW(self)
              state = calllib('edk','EE_EngineGetNextEvent',self.eEvent); 
              if state~=0 % state = 0 if everything's OK
                  warning('Everything is NOT OK: Is the headset connected, turned on, and on someone''s head?'); %#ok<WNTAG>
              end

              eventType = calllib('edk','EE_EmoEngineEventGetType',self.eEvent);
              %disp(eventType);
              userID=libpointer('uint32Ptr',0);
              calllib('edk','EE_EmoEngineEventGetUserId',self.eEvent, userID);

              if strcmp(eventType,'EE_UserAdded') == true
                  userID_value = get(userID,'value');
                  calllib('edk','EE_DataAcquisitionEnable',userID_value,true);
              end

              calllib('edk','EE_DataUpdateHandle', 0, self.hData);
              nSamples = libpointer('uint32Ptr',0);
              calllib('edk','EE_DataGetNumberOfSample', self.hData, nSamples);

              nSamplesTaken = get(nSamples,'value') ;
              if (nSamplesTaken ~= 0)
                  % Should check this and only get data if full amount is  available and new 
                  % (it is required for the get call to know how big dataPtr is)
                  if self.showDebug  
                      disp(['nSamplesTaken = ',num2str(nSamplesTaken)])
                  end

                  % Assign memory for the number (in lib) for samples taken on a single channel
                  channelDataPtr = libpointer('doublePtr',zeros(1,nSamplesTaken));

                  % Push the old values of the end, move newest ones to end
                  self.tempData = zeros(nSamplesTaken,self.channelCount);

                  % Go through each of the channels and get all the samples for that channel
                  for i = 1:length(fieldnames(self.EE_DataChannels_enum))
                      calllib('edk','EE_DataGet',self.hData, self.DataChannels.([self.DataChannelsNames{i}]), channelDataPtr, uint32(nSamplesTaken));
                      channelData = get(channelDataPtr,'value');
                      % Fill in our matrix of the latest data                    
                      self.tempData(1:nSamplesTaken,i) = channelData;

                      if (nSamplesTaken~=length(channelData))
                          warning('The nSamplesTaken shoul == length(channelData), Ask Gavin'); %#ok<WNTAG>
                      end
                  end

                  % Required so data variable is safely available externally to work with,
                  % Only update the data once the samples from the most recent read operation have been added
  %                 self.data = self.tempData;
                  self.data = [self.data; self.tempData];
              end 
          end
      end
  end
```

