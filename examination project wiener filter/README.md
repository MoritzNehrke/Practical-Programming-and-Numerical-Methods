//-----------------------------------------------------------------------------------------------------------------------------
// This is the examination project of Moritz Nehrke developing and testing a wiener filter
//-----------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------
// Step 1: generate a noisy test signal
//-----------------------------------------------------------------------------------------------------------------------------

The code generates a noisy test signal. The test signal is a simple cosine and randomly generated noise. Obviously is this not the most realistic signal, but works perfectly to test the implemented FT routines and as a proof of concept. The noisy test signal is plotted and can be seen in noisysignal.pdf.

//-----------------------------------------------------------------------------------------------------------------------------
// Step 1.1: implement a DFT and inverse DFT routine and apply it to the test signal
//-----------------------------------------------------------------------------------------------------------------------------

ft.h/ft.cpp implement a DFT routine as explained in the lecture notes. Plotted in dftnoisysignal.pdf one can see the result of applying the DFT on the test signal. The result matches what one would expect and shows the peak at 1 and the mirror peak at 84.3. One can now apply the inverse DFT to get back the original signal. This can be very nicely seen in idftnoisysignal.pdf.

//-----------------------------------------------------------------------------------------------------------------------------
// Step 1.2: try an apmlitude and frequency filter to remove the noise 
//-----------------------------------------------------------------------------------------------------------------------------

Using the DFT of the signal one has to simple option to filter the signal. A frequency filter and a amplitude filter are implemented in ft.h/ft.cpp as described in the lecture notes. Both of them do a great job on this very simple test signal. This can be seen in filteredsignal.pdf.

//-----------------------------------------------------------------------------------------------------------------------------
// Step 1.3: implement a FFT and inverse FFT routine and apply it to the test signal
//-----------------------------------------------------------------------------------------------------------------------------

One problem of the DFT routine is the runtime. It has a runtime of O(N^2), which becomes slow very quickly. One solution is the FFT, it can reduce the runtime to O(NlogN). The Cooley-Tukey algorithm is implemented as a FFT routine in ft.h/ft.cpp and strongly oriented on the code provided in the lecture notes. In ifftnoisysignal.pdf one can see a quick forth and back transformation and that the FFT routine works.

//-----------------------------------------------------------------------------------------------------------------------------
// Step 1.4: compare the runtime of the DFT and FFT routine
//-----------------------------------------------------------------------------------------------------------------------------

The improvement in runtime is confirmed in runtime.pdf. The DFT routine can be nicely fitted by a N^2 curve. The FFT routine can not be fitted by a NlogN curve, but the improvement of ~ N can be seen nicely. One would assume at higher N the FFT can be fitted nicely to NlogN, but this is to time consuming to test.

//-----------------------------------------------------------------------------------------------------------------------------
// Step 2: generate a more difficult test signal (Breit-Wigner peak)
//-----------------------------------------------------------------------------------------------------------------------------

The code generates a more complicated signal, which is closely oriented on real life applications. The signal is a Breit-Wigner peak and randomly generated noise. Both filter options are tested on this signal. This is plotted in breitwigner.pdf. One can see that the filter work far worse than before, but considering their simplicity well enough.

//-----------------------------------------------------------------------------------------------------------------------------
// Step 2.1: convolve signal with a detector efficiency function
//-----------------------------------------------------------------------------------------------------------------------------

To make the scenario even more realistic the Breit-Wigner peak is getting convolved with a detector efficiency funtion (here. Gaussian). Both a convolution and a deconvolution routine can be found in ft.h/ft.cpp. The resulting signal can be seen in convolved.pdf.


//-----------------------------------------------------------------------------------------------------------------------------
// Step 2.2: naive deconvolution of the signal
//-----------------------------------------------------------------------------------------------------------------------------

FT makes the deconvolution of such a signal simple, if the convolution function is provided. A naive deconvolution is seen in deconvolved.pdf and is not usable as one can see. This is because if the DFT of the detector eﬀiciency has values close to zero it significantly amplifies the noise.

//-----------------------------------------------------------------------------------------------------------------------------
// Step 3: use the wiener filter instead
//-----------------------------------------------------------------------------------------------------------------------------

Instead on can use a wiener filter, here implemented in ft.h/ft.cpp. The wiener filter introduces a Levenberg-Marquardt
regularizer. The result of this can be seen in wiener.pdf.

//-----------------------------------------------------------------------------------------------------------------------------
// Step 3.1: use a minimization routine to find the optimal lambda
//-----------------------------------------------------------------------------------------------------------------------------

To find the optimal Levenberg-Marquardt regularizer one could use minimize the difference between the filtered signal and the original signal. Obviously in reality one does not have the original signal, but maybe some kind of calibration is possible. The code uses the newton_minimize routine from the homeworks to find the optimum. The result can be seen in wienerfinal.pdf

//-----------------------------------------------------------------------------------------------------------------------------
// Step 3.2: compare the lambdas for different noise strengths
//-----------------------------------------------------------------------------------------------------------------------------

One could wonder how the optimal Levenberg-Marquardt regularizer behaves for different noise strengths. A empirical observation can be seen in lambda.pdf and suggests a linear relation. In the lecture notes it says it should be on the order of noise/signal, the signal is not constant but nonetheless this fits.