function PulseRateConfigAndData = ...
             PulseRate_ControlForLuminance(PulseRateConfigAndData, FrameTimestamp_Double)
%PulseRate_ControlForLuminance    Statistically control the ROI mean values for luminance that 
%                                 varies across frames.
%
%    Helper function to function FacePulseRate.
%    Within function FacePulseRate, called by function PulseRate.
%
%
%    Description
%    -----------
%
%    Statistically control the ROI mean values for luminance that varies across frames. Controlling 
%    for luminance is based upon Madan et al. (2018). Madan et al. (2018) used L from the LAB 
%    colorspace, but Y from the YCbCr color space should be nearly equivalent. The option for Y is 
%    provided because producing it (in function ROIMeans_TakeMeans) is more computationally 
%    efficient as another function (SkinSegmentMask) has already converted RGB to YCbCr. 
%
%
%    Copyright
%    ---------
%
%    Copyright (c) 2020 Douglas Magill <dpmdpm@vt.edu>. Licensed under the GPL v.2 and RAIL 
%    licenses with exceptions noted in file FacePulseRate/License.txt. For interest in commercial  
%    licensing, please contact the author.

   
%Enclose linear regression within try-catch in case linear regression not successful
%If not successful, disable luminance control and continue.
try

    %Luminance mean is specified to be from YCbCr colorspace
    %Y is the luminance channel in the YCbCr colorspace.
    if PulseRateConfigAndData.ControlLuminanceColorspace == 'Y'

        %Fill in missing skin luminance means by linear interpolation
        %If no missing values present, function will return values unmodified.
        %Note: missing values may occur intentionally. For example, if the entire ROI happens to be
        %segmented out -- which might occur, for example, if a page is flipped in front of the 
        %camera -- there will be no values with which to compute the mean because segmented pixels
        %are excluded from the mean calculation.
        %Type double.
        PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr = ...
            fillmissing(PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr, ...
            'linear',  'SamplePoints', FrameTimestamp_Double);

        %Red channel luminance-controlled means
        %Type double.
        LinRegModelR = fitlm(PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr, ...
            PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 1));

        %Green channel luminance-controlled means
        %Type double.
        LinRegModelG = fitlm(PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr, ...
            PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 2));

        %Blue channel luminance-controlled means
        %Type double.
        LinRegModelB = fitlm(PulseRateConfigAndData.ColorData.SkinLuminanceMeans.Y_of_YCbCr, ...
            PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 3));
    
    %Luminance mean is specified to be from LAB colorspace
    %L is the luminance channel in the LAB colorspace.
    %For LAB implementation, see Madan et al. (2018)
    elseif PulseRateConfigAndData.ControlLuminanceColorspace == 'L'       

        %Fill in missing skin luminance means by linear interpolation
        %Note: if no missing values present, function will return values unmodified.
        %Type double.
        PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB = ...
            fillmissing(PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB, 'linear', ...
                'SamplePoints', FrameTimestamp_Double);

        %Red channel luminance-controlled means
        %Type double.
        LinRegModelR = ...
            fitlm(PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB, ...
                PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 1));

        %Green channel luminance-controlled means
        %Type double.
        LinRegModelG = ...
            fitlm(PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB, ...
                PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 2));

        %Blue channel luminance-controlled means
        %Type double.
        LinRegModelB = ...
            fitlm(PulseRateConfigAndData.ColorData.SkinLuminanceMeans.L_of_LAB, ...
                PulseRateConfigAndData.ColorData.SkinRGBMeans(:, 3));
    end

    %Concatenate; make non-negative
    %Type double.
    PulseRateConfigAndData.ColorData.SkinRGBMeans_LumControl = ...
        [LinRegModelR.Residuals.Raw + 100, ...
         LinRegModelG.Residuals.Raw + 100, ...
         LinRegModelB.Residuals.Raw + 100];  

    %Check whether missing (NaN) values were returned from linear regression for any reason
    %If so, disable controlling for luminance and display warning message.
    if any( isnan(PulseRateConfigAndData.ColorData.SkinRGBMeans_LumControl), 'all' )

        %Disable luminance control
        PulseRateConfigAndData.ControlLuminanceTF = false;

        %Display warning message
        warning( ...
            ['The return values after controlling for luminance contained missing values,', ... 
             ' which could indicate that the linear regression performed to extract the', ... 
             ' residuals was not successful. In order to continue, controlling for luminance', ...
             ' will be disabled.'] ...
         );
    end    

%Linear regression not successful
%Disable controlling for luminance and display warning message.
catch

    %Disable luminance control
    PulseRateConfigAndData.ControlLuminanceTF = false;
    
    %Assign empty output argument
    PulseRateConfigAndData.ColorData.SkinRGBMeans_LumControl = [];

    %Display warning message
    warning( ...
        ['The linear regression performed in order to control for luminance was not', ... 
         ' successful. Controlling for luminance will be disabled in order to continue.'] ... 
     );       
end


end %end function

