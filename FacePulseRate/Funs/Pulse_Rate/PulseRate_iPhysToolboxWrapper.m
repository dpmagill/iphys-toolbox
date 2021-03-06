function [BVP_jthWindow, PR_jthWindow] = ...
             PulseRate_iPhysToolboxWrapper(Alg, SkinRGBMeansWindow, VideoReadConfig, TWindow, ...
                 GeneralValidationCompleted_TF)
%PulseRate_iPhysToolboxWrapper   A wrapper function for the functions in iPhys Toolbox for use in 
%                                FacePulseRate.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function PulseRate_Algorithms.
%
%
%    Description
%    -----------
%
%    A wrapper function for the functions in iPhys Toolbox (McDuff & Blackford, 2019) for use in 
%    FacePulseRate. The files for these functions and helper functions, as well as the  
%    corresponding licenses, can be found in folder 
%    '.../FacePulseRate/Funs/PulseRate/iPhysToolbox_modified'. 
%    
%                      
%    References
%    ---------- 
%
%    McDuff, D., & Blackford, E. (2019). iphys: An open non-contact imaging-based physiological 
%    measurement toolbox. In 2019 Annual International Conference of the IEEE Engineering in 
%    Medicine and Biology Society (EMBC), pp. 6521-6524. 
%
%
%    Pulse-Rate Algorithm Third-Party Copyright Notices
%    --------------------------------------------------
%
%    Third-party copyrights are property of their respective owners.
%
%    The following files are based in whole or in part on the implementation in iPhys Toolbox,  
%    copyright (c) Daniel McDuff, Ethan Blackford, January 2019, licensed under the MIT License and 
%    the Responsible AI License (RAIL). 
%   
%        CHROM_DEHAAN.m ("Chrominance" method). See discussion in De Haan, G., & Jeanne, V. (2013).   
%        Robust pulse rate from chrominance-based rPPG. IEEE Transactions on Biomedical   
%        Engineering, 60(10), 2878-2886. DOI: 10.1109/TBME.2013.2266196
%
%        GREEN_VERKRUYSSE.m ("Green-Channel" method). See discussion in Verkruysse, W., Svaasand,     
%        L. O., & Nelson, J. S. (2008). Remote plethysmographic imaging using ambient light. Optics   
%        express, 16(26), 21434-21445. DOI: 10.1364/OE.16.021434
%
%        ICA_POH.m ("Independent Component Analysis [ICA]" method). See discussion in Poh, M. Z., 
%        McDuff, D. J., & Picard, R. W. (2010). Non-contact, automated cardiac pulse measurements  
%        using video imaging and blind source separation. Optics express, 18(10), 10762-10774. DOI: 
%        10.1364/OE.18.010762   
%
%        POS_WANG.m ("Plane Orthogonal to Skin-Tone [POS]" method). See discussion in Wang, W., den   
%        Brinker, A. C., Stuijk, S., & de Haan, G. (2017). Algorithmic principles of remote PPG.  
%        IEEE Transactions on Biomedical Engineering, 64(7), 1479-1491. DOI: 
%        10.1109/TBME.2016.2609282    
%
%        ICA.m. Daniel McDuff, Ethan Blackford, & Justin Estepp, December, 2018. Based on an 
%        implementation by: G. D. Clifford (2004) <gari@mit.edu>. Licensed under the MIT License   
%        and the Responsible AI License (RAIL).
% 
%        jade.m. J. F. Cardoso, Version 1.5. See discussion in Cardoso, J. C. C. O., & Souloumiac,  
%        A. Blind beamforming for non-Gaussian signals. 1993. IET. p, 362-370.
%
%        spdetrend.m. Implementation based on M. P. Tarvainen, TBME, 2002.  
%
%        bvpsnr.m. Adapted from the method by G. de Haan, TBME, 2013.
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.


%%%%%% Specify additional input arguments %%%%%%

%Argument specific to POS_WANG algorithm
if Alg == 'P'
    
    %Color-distortion filtering
    %Only used for function POS_WANG.
    useFGTransformTF = true;
end

%Argument specific to CHROM_DEHAAN algorithm
if Alg == 'C'
    
    %See function CHROM_DEHAAN_modified  
    WinSec = 1.6;
    
    %Number of frames corresponding to jth window
    nFramesWindow = length(TWindow);     
end


%%%%%% Input validation %%%%%%

%%%%%% --- General input validation %%%%%%

%If the general input validation has been previously conducted
if GeneralValidationCompleted_TF

    %Display error message and stop function if Signal Processing Toolbox not installed
    %Note: this check is also conducted by function ValidateAndConfigure_Validate.
    if ~ license('test', 'signal_toolbox') %test whether Signal Processing Toolbox installed 

        ME = ...
            MException('Component:Toolbox', ...
                'Error: Filtering and periodogram require: Signal Processing Toolbox' ...
            );

        throw(ME);
    end

    %If NaN present in RGB, an error will occur.      
    if any( isnan(SkinRGBMeansWindow), 'all' )

        ME = ...
            MException('Component:Argument', ...
                'Internal Error: Pulse-rate algorithms cannot accept RGB values that include', ...
                ' NaN.' ...
            );

        throw(ME);    
    end 

    %If values of RGB are zero, NaN will end up being assigned to Xs by algorithms. If Xs is NaN, 
    %function filtfilt, which is called by algorithms, will throw an error.
    if any( SkinRGBMeansWindow == 0, 'all' )

        ME = ...
            MException('Component:Argument', ...
                'Internal Error: The RGB input matrix must not contain zeros.' ...
            );

        throw(ME);
    end
end

%%%%%% --- Algorithm-specific input validation %%%%%%

%Input validation specifically for CHROM_DEHAAN algorithm
if Alg == 'C'   

    %If fewer frames used (nFramesWindow) than ceil(WinSec * FS), an error will occur in 
    %function CHROM_DEHAAN_modified.
    if WinSec * VideoReadConfig.FS > nFramesWindow

        ME = ...
            MException('Component:Argument', ...
                 ['Error: For proper functioning of the CHROM_DEHAAN algorithm, the number of', ...
                  ' frames processed must be equal to or greater than', ...
                  ' ceil(', num2str(WinSec), ' * FS).'] ...
             );

        throw(ME);
    end
end


%%%%%% Call specified algorithm from iPhys Toolbox %%%%%%

%Return the pulse rate and BVP for jth window using the specified algorithm. The functions below
%are custom functions located within folder 'FacePulseRate'. They are modified functions from iPhys
%Toolbox.

switch Alg
    
    %CHROM_DEHAAN
    case 'C'
                
        [BVP_jthWindow, PR_jthWindow] = ...
            CHROM_DEHAAN_modified(SkinRGBMeansWindow, VideoReadConfig.FS, TWindow, WinSec, ...
                nFramesWindow);
        
    %GREEN_VERKRUYSSE    
    case 'G'       
        
        [BVP_jthWindow, PR_jthWindow] = ...
            GREEN_VERKRUYSSE_modified(SkinRGBMeansWindow, VideoReadConfig.FS);
        
    %ICA_POH
    case 'I'        
        
        [BVP_jthWindow, PR_jthWindow] = ...
            ICA_POH_modified(SkinRGBMeansWindow, VideoReadConfig.FS);
        
    %POS_WANG
    case 'P'
        
        [BVP_jthWindow, PR_jthWindow] = ...
            POS_WANG_modified(SkinRGBMeansWindow, VideoReadConfig.FS, useFGTransformTF);
end


end %end function

