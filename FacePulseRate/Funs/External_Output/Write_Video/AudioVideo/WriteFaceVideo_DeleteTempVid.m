function WriteFaceVideo_DeleteTempVid(OutputFile_OnlyVideo)
%WriteFaceVideo_DeleteTempVid   Delete temporary video at termination of function WriteFaceVideo.
%
%    Helper function to function FacePulseRate. 
%    Within function FacePulseRate, called by function WriteFaceVideo. 
%
%
%    Description
%    -----------
% 
%    Delete temporary video at termination of function WriteFaceVideo.
%
%    For description, see bottom of function WriteFaceVideo_InitializeWriter where object 
%    cleanupObj2 is assigned. 


if isfile(OutputFile_OnlyVideo)
    
    delete(OutputFile_OnlyVideo)
end


end %end function

