module dut (out, in);
	output[6:0] out;
	input[35:0] in;
	wire xformtmp175815;
	assign xformtmp175815 = ~in[0];
	wire xformtmp175814;
	assign xformtmp175814 = in[1] & xformtmp175815;
	wire xformtmp175813;
	assign xformtmp175813 = ~xformtmp175814;
	wire xformtmp175819;
	assign xformtmp175819 = ~in[3];
	wire xformtmp175818;
	assign xformtmp175818 = in[5] & xformtmp175819;
	wire xformtmp175817;
	assign xformtmp175817 = ~xformtmp175818;
	wire xformtmp175823;
	assign xformtmp175823 = ~in[7];
	wire xformtmp175822;
	assign xformtmp175822 = in[9] & xformtmp175823;
	wire xformtmp175821;
	assign xformtmp175821 = ~xformtmp175822;
	wire xformtmp175827;
	assign xformtmp175827 = ~in[11];
	wire xformtmp175826;
	assign xformtmp175826 = in[13] & xformtmp175827;
	wire xformtmp175825;
	assign xformtmp175825 = ~xformtmp175826;
	wire xformtmp175831;
	assign xformtmp175831 = ~in[15];
	wire xformtmp175830;
	assign xformtmp175830 = in[17] & xformtmp175831;
	wire xformtmp175829;
	assign xformtmp175829 = ~xformtmp175830;
	wire xformtmp175835;
	assign xformtmp175835 = ~in[19];
	wire xformtmp175834;
	assign xformtmp175834 = in[21] & xformtmp175835;
	wire xformtmp175833;
	assign xformtmp175833 = ~xformtmp175834;
	wire xformtmp175839;
	assign xformtmp175839 = ~in[23];
	wire xformtmp175838;
	assign xformtmp175838 = in[25] & xformtmp175839;
	wire xformtmp175837;
	assign xformtmp175837 = ~xformtmp175838;
	wire xformtmp175843;
	assign xformtmp175843 = ~in[27];
	wire xformtmp175842;
	assign xformtmp175842 = in[29] & xformtmp175843;
	wire xformtmp175841;
	assign xformtmp175841 = ~xformtmp175842;
	wire xformtmp175849;
	assign xformtmp175849 = ~in[31];
	wire xformtmp175848;
	assign xformtmp175848 = in[33] & xformtmp175849;
	wire xformtmp175847;
	assign xformtmp175847 = ~xformtmp175848;
	wire xformtmp175840;
	assign xformtmp175840 = xformtmp175841 & xformtmp175847;
	wire xformtmp175836;
	assign xformtmp175836 = xformtmp175837 & xformtmp175840;
	wire xformtmp175832;
	assign xformtmp175832 = xformtmp175833 & xformtmp175836;
	wire xformtmp175828;
	assign xformtmp175828 = xformtmp175829 & xformtmp175832;
	wire xformtmp175824;
	assign xformtmp175824 = xformtmp175825 & xformtmp175828;
	wire xformtmp175820;
	assign xformtmp175820 = xformtmp175821 & xformtmp175824;
	wire xformtmp175816;
	assign xformtmp175816 = xformtmp175817 & xformtmp175820;
	wire xformtmp175812;
	assign xformtmp175812 = xformtmp175813 & xformtmp175816;
	assign out[0] = ~xformtmp175812;
	wire xformtmp175397;
	assign xformtmp175397 = ~in[1];
	wire xformtmp175396;
	assign xformtmp175396 = in[2] | xformtmp175397;
	wire xformtmp175395;
	assign xformtmp175395 = ~xformtmp175396;
	wire xformtmp175811;
	assign xformtmp175811 = ~xformtmp175812;
	wire xformtmp175398;
	assign xformtmp175398 = xformtmp175811 ^ xformtmp175813;
	wire xformtmp175394;
	assign xformtmp175394 = xformtmp175395 & xformtmp175398;
	wire xformtmp175393;
	assign xformtmp175393 = ~xformtmp175394;
	wire xformtmp175443;
	assign xformtmp175443 = ~in[5];
	wire xformtmp175442;
	assign xformtmp175442 = in[6] | xformtmp175443;
	wire xformtmp175441;
	assign xformtmp175441 = ~xformtmp175442;
	wire xformtmp175444;
	assign xformtmp175444 = xformtmp175811 ^ xformtmp175817;
	wire xformtmp175440;
	assign xformtmp175440 = xformtmp175441 & xformtmp175444;
	wire xformtmp175439;
	assign xformtmp175439 = ~xformtmp175440;
	wire xformtmp175489;
	assign xformtmp175489 = ~in[9];
	wire xformtmp175488;
	assign xformtmp175488 = in[10] | xformtmp175489;
	wire xformtmp175487;
	assign xformtmp175487 = ~xformtmp175488;
	wire xformtmp175490;
	assign xformtmp175490 = xformtmp175811 ^ xformtmp175821;
	wire xformtmp175486;
	assign xformtmp175486 = xformtmp175487 & xformtmp175490;
	wire xformtmp175485;
	assign xformtmp175485 = ~xformtmp175486;
	wire xformtmp175535;
	assign xformtmp175535 = ~in[13];
	wire xformtmp175534;
	assign xformtmp175534 = in[14] | xformtmp175535;
	wire xformtmp175533;
	assign xformtmp175533 = ~xformtmp175534;
	wire xformtmp175536;
	assign xformtmp175536 = xformtmp175811 ^ xformtmp175825;
	wire xformtmp175532;
	assign xformtmp175532 = xformtmp175533 & xformtmp175536;
	wire xformtmp175531;
	assign xformtmp175531 = ~xformtmp175532;
	wire xformtmp175581;
	assign xformtmp175581 = ~in[17];
	wire xformtmp175580;
	assign xformtmp175580 = in[18] | xformtmp175581;
	wire xformtmp175579;
	assign xformtmp175579 = ~xformtmp175580;
	wire xformtmp175582;
	assign xformtmp175582 = xformtmp175811 ^ xformtmp175829;
	wire xformtmp175578;
	assign xformtmp175578 = xformtmp175579 & xformtmp175582;
	wire xformtmp175577;
	assign xformtmp175577 = ~xformtmp175578;
	wire xformtmp175627;
	assign xformtmp175627 = ~in[21];
	wire xformtmp175626;
	assign xformtmp175626 = in[22] | xformtmp175627;
	wire xformtmp175625;
	assign xformtmp175625 = ~xformtmp175626;
	wire xformtmp175628;
	assign xformtmp175628 = xformtmp175811 ^ xformtmp175833;
	wire xformtmp175624;
	assign xformtmp175624 = xformtmp175625 & xformtmp175628;
	wire xformtmp175623;
	assign xformtmp175623 = ~xformtmp175624;
	wire xformtmp175673;
	assign xformtmp175673 = ~in[25];
	wire xformtmp175672;
	assign xformtmp175672 = in[26] | xformtmp175673;
	wire xformtmp175671;
	assign xformtmp175671 = ~xformtmp175672;
	wire xformtmp175674;
	assign xformtmp175674 = xformtmp175811 ^ xformtmp175837;
	wire xformtmp175670;
	assign xformtmp175670 = xformtmp175671 & xformtmp175674;
	wire xformtmp175669;
	assign xformtmp175669 = ~xformtmp175670;
	wire xformtmp175719;
	assign xformtmp175719 = ~in[29];
	wire xformtmp175718;
	assign xformtmp175718 = in[30] | xformtmp175719;
	wire xformtmp175717;
	assign xformtmp175717 = ~xformtmp175718;
	wire xformtmp175720;
	assign xformtmp175720 = xformtmp175811 ^ xformtmp175841;
	wire xformtmp175716;
	assign xformtmp175716 = xformtmp175717 & xformtmp175720;
	wire xformtmp175715;
	assign xformtmp175715 = ~xformtmp175716;
	wire xformtmp175809;
	assign xformtmp175809 = ~in[33];
	wire xformtmp175808;
	assign xformtmp175808 = in[34] | xformtmp175809;
	wire xformtmp175807;
	assign xformtmp175807 = ~xformtmp175808;
	wire xformtmp175810;
	assign xformtmp175810 = xformtmp175811 ^ xformtmp175847;
	wire xformtmp175806;
	assign xformtmp175806 = xformtmp175807 & xformtmp175810;
	wire xformtmp175805;
	assign xformtmp175805 = ~xformtmp175806;
	wire xformtmp175714;
	assign xformtmp175714 = xformtmp175715 & xformtmp175805;
	wire xformtmp175668;
	assign xformtmp175668 = xformtmp175669 & xformtmp175714;
	wire xformtmp175622;
	assign xformtmp175622 = xformtmp175623 & xformtmp175668;
	wire xformtmp175576;
	assign xformtmp175576 = xformtmp175577 & xformtmp175622;
	wire xformtmp175530;
	assign xformtmp175530 = xformtmp175531 & xformtmp175576;
	wire xformtmp175484;
	assign xformtmp175484 = xformtmp175485 & xformtmp175530;
	wire xformtmp175438;
	assign xformtmp175438 = xformtmp175439 & xformtmp175484;
	wire xformtmp175392;
	assign xformtmp175392 = xformtmp175393 & xformtmp175438;
	assign out[1] = ~xformtmp175392;
	wire xformtmp171293;
	assign xformtmp171293 = in[4] | xformtmp175397;
	wire xformtmp171292;
	assign xformtmp171292 = ~xformtmp171293;
	wire xformtmp171291;
	assign xformtmp171291 = xformtmp171292 & xformtmp175398;
	wire xformtmp175391;
	assign xformtmp175391 = ~xformtmp175392;
	wire xformtmp171335;
	assign xformtmp171335 = xformtmp175391 ^ xformtmp175393;
	wire xformtmp171290;
	assign xformtmp171290 = xformtmp171291 & xformtmp171335;
	wire xformtmp171289;
	assign xformtmp171289 = ~xformtmp171290;
	wire xformtmp171800;
	assign xformtmp171800 = in[8] | xformtmp175443;
	wire xformtmp171799;
	assign xformtmp171799 = ~xformtmp171800;
	wire xformtmp171798;
	assign xformtmp171798 = xformtmp171799 & xformtmp175444;
	wire xformtmp171842;
	assign xformtmp171842 = xformtmp175391 ^ xformtmp175439;
	wire xformtmp171797;
	assign xformtmp171797 = xformtmp171798 & xformtmp171842;
	wire xformtmp171796;
	assign xformtmp171796 = ~xformtmp171797;
	wire xformtmp172307;
	assign xformtmp172307 = in[12] | xformtmp175489;
	wire xformtmp172306;
	assign xformtmp172306 = ~xformtmp172307;
	wire xformtmp172305;
	assign xformtmp172305 = xformtmp172306 & xformtmp175490;
	wire xformtmp172349;
	assign xformtmp172349 = xformtmp175391 ^ xformtmp175485;
	wire xformtmp172304;
	assign xformtmp172304 = xformtmp172305 & xformtmp172349;
	wire xformtmp172303;
	assign xformtmp172303 = ~xformtmp172304;
	wire xformtmp172814;
	assign xformtmp172814 = in[16] | xformtmp175535;
	wire xformtmp172813;
	assign xformtmp172813 = ~xformtmp172814;
	wire xformtmp172812;
	assign xformtmp172812 = xformtmp172813 & xformtmp175536;
	wire xformtmp172856;
	assign xformtmp172856 = xformtmp175391 ^ xformtmp175531;
	wire xformtmp172811;
	assign xformtmp172811 = xformtmp172812 & xformtmp172856;
	wire xformtmp172810;
	assign xformtmp172810 = ~xformtmp172811;
	wire xformtmp173321;
	assign xformtmp173321 = in[20] | xformtmp175581;
	wire xformtmp173320;
	assign xformtmp173320 = ~xformtmp173321;
	wire xformtmp173319;
	assign xformtmp173319 = xformtmp173320 & xformtmp175582;
	wire xformtmp173363;
	assign xformtmp173363 = xformtmp175391 ^ xformtmp175577;
	wire xformtmp173318;
	assign xformtmp173318 = xformtmp173319 & xformtmp173363;
	wire xformtmp173317;
	assign xformtmp173317 = ~xformtmp173318;
	wire xformtmp173828;
	assign xformtmp173828 = in[24] | xformtmp175627;
	wire xformtmp173827;
	assign xformtmp173827 = ~xformtmp173828;
	wire xformtmp173826;
	assign xformtmp173826 = xformtmp173827 & xformtmp175628;
	wire xformtmp173870;
	assign xformtmp173870 = xformtmp175391 ^ xformtmp175623;
	wire xformtmp173825;
	assign xformtmp173825 = xformtmp173826 & xformtmp173870;
	wire xformtmp173824;
	assign xformtmp173824 = ~xformtmp173825;
	wire xformtmp174335;
	assign xformtmp174335 = in[28] | xformtmp175673;
	wire xformtmp174334;
	assign xformtmp174334 = ~xformtmp174335;
	wire xformtmp174333;
	assign xformtmp174333 = xformtmp174334 & xformtmp175674;
	wire xformtmp174377;
	assign xformtmp174377 = xformtmp175391 ^ xformtmp175669;
	wire xformtmp174332;
	assign xformtmp174332 = xformtmp174333 & xformtmp174377;
	wire xformtmp174331;
	assign xformtmp174331 = ~xformtmp174332;
	wire xformtmp174842;
	assign xformtmp174842 = in[32] | xformtmp175719;
	wire xformtmp174841;
	assign xformtmp174841 = ~xformtmp174842;
	wire xformtmp174840;
	assign xformtmp174840 = xformtmp174841 & xformtmp175720;
	wire xformtmp174884;
	assign xformtmp174884 = xformtmp175391 ^ xformtmp175715;
	wire xformtmp174839;
	assign xformtmp174839 = xformtmp174840 & xformtmp174884;
	wire xformtmp174838;
	assign xformtmp174838 = ~xformtmp174839;
	wire xformtmp175348;
	assign xformtmp175348 = in[35] | xformtmp175809;
	wire xformtmp175347;
	assign xformtmp175347 = ~xformtmp175348;
	wire xformtmp175346;
	assign xformtmp175346 = xformtmp175347 & xformtmp175810;
	wire xformtmp175390;
	assign xformtmp175390 = xformtmp175391 ^ xformtmp175805;
	wire xformtmp175345;
	assign xformtmp175345 = xformtmp175346 & xformtmp175390;
	wire xformtmp175344;
	assign xformtmp175344 = ~xformtmp175345;
	wire xformtmp174837;
	assign xformtmp174837 = xformtmp174838 & xformtmp175344;
	wire xformtmp174330;
	assign xformtmp174330 = xformtmp174331 & xformtmp174837;
	wire xformtmp173823;
	assign xformtmp173823 = xformtmp173824 & xformtmp174330;
	wire xformtmp173316;
	assign xformtmp173316 = xformtmp173317 & xformtmp173823;
	wire xformtmp172809;
	assign xformtmp172809 = xformtmp172810 & xformtmp173316;
	wire xformtmp172302;
	assign xformtmp172302 = xformtmp172303 & xformtmp172809;
	wire xformtmp171795;
	assign xformtmp171795 = xformtmp171796 & xformtmp172302;
	wire xformtmp171288;
	assign xformtmp171288 = xformtmp171289 & xformtmp171795;
	assign out[2] = ~xformtmp171288;
	wire xformtmp90;
	assign xformtmp90 = in[0] & xformtmp175811;
	wire xformtmp89;
	assign xformtmp89 = ~xformtmp90;
	wire xformtmp170;
	assign xformtmp170 = in[2] & xformtmp175391;
	wire xformtmp169;
	assign xformtmp169 = ~xformtmp170;
	wire xformtmp171287;
	assign xformtmp171287 = ~xformtmp171288;
	wire xformtmp220;
	assign xformtmp220 = in[4] & xformtmp171287;
	wire xformtmp219;
	assign xformtmp219 = ~xformtmp220;
	wire xformtmp238;
	assign xformtmp238 = xformtmp169 & xformtmp219;
	wire xformtmp239;
	assign xformtmp239 = xformtmp89 & xformtmp238;
	wire xformtmp240;
	assign xformtmp240 = in[1] & xformtmp239;
	wire xformtmp170830;
	assign xformtmp170830 = in[3] & xformtmp175811;
	wire xformtmp170829;
	assign xformtmp170829 = ~xformtmp170830;
	wire xformtmp170869;
	assign xformtmp170869 = in[6] & xformtmp175391;
	wire xformtmp170868;
	assign xformtmp170868 = ~xformtmp170869;
	wire xformtmp171286;
	assign xformtmp171286 = in[8] & xformtmp171287;
	wire xformtmp171285;
	assign xformtmp171285 = ~xformtmp171286;
	wire xformtmp171284;
	assign xformtmp171284 = in[5] & xformtmp171285;
	wire xformtmp170867;
	assign xformtmp170867 = xformtmp170868 & xformtmp171284;
	wire xformtmp170828;
	assign xformtmp170828 = xformtmp170829 & xformtmp170867;
	wire xformtmp241;
	assign xformtmp241 = ~xformtmp170828;
	wire xformtmp160786;
	assign xformtmp160786 = in[7] & xformtmp175811;
	wire xformtmp160785;
	assign xformtmp160785 = ~xformtmp160786;
	wire xformtmp160825;
	assign xformtmp160825 = in[10] & xformtmp175391;
	wire xformtmp160824;
	assign xformtmp160824 = ~xformtmp160825;
	wire xformtmp161242;
	assign xformtmp161242 = in[12] & xformtmp171287;
	wire xformtmp161241;
	assign xformtmp161241 = ~xformtmp161242;
	wire xformtmp161240;
	assign xformtmp161240 = in[9] & xformtmp161241;
	wire xformtmp160823;
	assign xformtmp160823 = xformtmp160824 & xformtmp161240;
	wire xformtmp160784;
	assign xformtmp160784 = xformtmp160785 & xformtmp160823;
	wire xformtmp160783;
	assign xformtmp160783 = ~xformtmp160784;
	wire xformtmp165808;
	assign xformtmp165808 = in[11] & xformtmp175811;
	wire xformtmp165807;
	assign xformtmp165807 = ~xformtmp165808;
	wire xformtmp165847;
	assign xformtmp165847 = in[14] & xformtmp175391;
	wire xformtmp165846;
	assign xformtmp165846 = ~xformtmp165847;
	wire xformtmp166264;
	assign xformtmp166264 = in[16] & xformtmp171287;
	wire xformtmp166263;
	assign xformtmp166263 = ~xformtmp166264;
	wire xformtmp166262;
	assign xformtmp166262 = in[13] & xformtmp166263;
	wire xformtmp165845;
	assign xformtmp165845 = xformtmp165846 & xformtmp166262;
	wire xformtmp165806;
	assign xformtmp165806 = xformtmp165807 & xformtmp165845;
	wire xformtmp130648;
	assign xformtmp130648 = ~xformtmp165806;
	wire xformtmp60338;
	assign xformtmp60338 = in[15] & xformtmp175811;
	wire xformtmp60337;
	assign xformtmp60337 = ~xformtmp60338;
	wire xformtmp60377;
	assign xformtmp60377 = in[18] & xformtmp175391;
	wire xformtmp60376;
	assign xformtmp60376 = ~xformtmp60377;
	wire xformtmp60794;
	assign xformtmp60794 = in[20] & xformtmp171287;
	wire xformtmp60793;
	assign xformtmp60793 = ~xformtmp60794;
	wire xformtmp60792;
	assign xformtmp60792 = in[17] & xformtmp60793;
	wire xformtmp60375;
	assign xformtmp60375 = xformtmp60376 & xformtmp60792;
	wire xformtmp60336;
	assign xformtmp60336 = xformtmp60337 & xformtmp60375;
	wire xformtmp253;
	assign xformtmp253 = ~xformtmp60336;
	wire xformtmp103;
	assign xformtmp103 = in[19] & xformtmp175811;
	wire xformtmp102;
	assign xformtmp102 = ~xformtmp103;
	wire xformtmp185;
	assign xformtmp185 = in[22] & xformtmp175391;
	wire xformtmp184;
	assign xformtmp184 = ~xformtmp185;
	wire xformtmp230;
	assign xformtmp230 = in[24] & xformtmp171287;
	wire xformtmp229;
	assign xformtmp229 = ~xformtmp230;
	wire xformtmp258;
	assign xformtmp258 = in[21] & xformtmp229;
	wire xformtmp259;
	assign xformtmp259 = xformtmp184 & xformtmp258;
	wire xformtmp260;
	assign xformtmp260 = xformtmp102 & xformtmp259;
	wire xformtmp257;
	assign xformtmp257 = ~xformtmp260;
	wire xformtmp140696;
	assign xformtmp140696 = in[23] & xformtmp175811;
	wire xformtmp140695;
	assign xformtmp140695 = ~xformtmp140696;
	wire xformtmp140735;
	assign xformtmp140735 = in[26] & xformtmp175391;
	wire xformtmp140734;
	assign xformtmp140734 = ~xformtmp140735;
	wire xformtmp141152;
	assign xformtmp141152 = in[28] & xformtmp171287;
	wire xformtmp141151;
	assign xformtmp141151 = ~xformtmp141152;
	wire xformtmp141150;
	assign xformtmp141150 = in[25] & xformtmp141151;
	wire xformtmp140733;
	assign xformtmp140733 = xformtmp140734 & xformtmp141150;
	wire xformtmp140694;
	assign xformtmp140694 = xformtmp140695 & xformtmp140733;
	wire xformtmp261;
	assign xformtmp261 = ~xformtmp140694;
	wire xformtmp145718;
	assign xformtmp145718 = in[27] & xformtmp175811;
	wire xformtmp145717;
	assign xformtmp145717 = ~xformtmp145718;
	wire xformtmp145757;
	assign xformtmp145757 = in[30] & xformtmp175391;
	wire xformtmp145756;
	assign xformtmp145756 = ~xformtmp145757;
	wire xformtmp146174;
	assign xformtmp146174 = in[32] & xformtmp171287;
	wire xformtmp146173;
	assign xformtmp146173 = ~xformtmp146174;
	wire xformtmp146172;
	assign xformtmp146172 = in[29] & xformtmp146173;
	wire xformtmp145755;
	assign xformtmp145755 = xformtmp145756 & xformtmp146172;
	wire xformtmp145716;
	assign xformtmp145716 = xformtmp145717 & xformtmp145755;
	wire xformtmp265;
	assign xformtmp265 = ~xformtmp145716;
	wire xformtmp109;
	assign xformtmp109 = in[31] & xformtmp175811;
	wire xformtmp108;
	assign xformtmp108 = ~xformtmp109;
	wire xformtmp191;
	assign xformtmp191 = in[34] & xformtmp175391;
	wire xformtmp190;
	assign xformtmp190 = ~xformtmp191;
	wire xformtmp236;
	assign xformtmp236 = in[35] & xformtmp171287;
	wire xformtmp235;
	assign xformtmp235 = ~xformtmp236;
	wire xformtmp270;
	assign xformtmp270 = in[33] & xformtmp235;
	wire xformtmp271;
	assign xformtmp271 = xformtmp190 & xformtmp270;
	wire xformtmp272;
	assign xformtmp272 = xformtmp108 & xformtmp271;
	wire xformtmp269;
	assign xformtmp269 = ~xformtmp272;
	wire xformtmp275;
	assign xformtmp275 = xformtmp265 & xformtmp269;
	wire xformtmp276;
	assign xformtmp276 = xformtmp261 & xformtmp275;
	wire xformtmp277;
	assign xformtmp277 = xformtmp257 & xformtmp276;
	wire xformtmp278;
	assign xformtmp278 = xformtmp253 & xformtmp277;
	wire xformtmp279;
	assign xformtmp279 = xformtmp130648 & xformtmp278;
	wire xformtmp280;
	assign xformtmp280 = xformtmp160783 & xformtmp279;
	wire xformtmp274;
	assign xformtmp274 = xformtmp241 & xformtmp280;
	wire xformtmp285;
	assign xformtmp285 = xformtmp240 | xformtmp274;
	assign out[3] = ~xformtmp285;
	wire xformtmp160782;
	assign xformtmp160782 = xformtmp160783 & xformtmp165806;
	wire xformtmp286;
	assign xformtmp286 = ~xformtmp160782;
	wire xformtmp299;
	assign xformtmp299 = xformtmp286 & xformtmp253;
	wire xformtmp300;
	assign xformtmp300 = xformtmp299 & xformtmp160783;
	wire xformtmp301;
	assign xformtmp301 = xformtmp300 & xformtmp241;
	assign out[4] = ~xformtmp301;
	wire xformtmp289;
	assign xformtmp289 = xformtmp253 & xformtmp260;
	wire xformtmp290;
	assign xformtmp290 = xformtmp289 & xformtmp130648;
	wire xformtmp291;
	assign xformtmp291 = xformtmp290 & xformtmp160783;
	wire xformtmp288;
	assign xformtmp288 = ~xformtmp291;
	wire xformtmp293;
	assign xformtmp293 = xformtmp130648 & xformtmp140694;
	wire xformtmp294;
	assign xformtmp294 = xformtmp293 & xformtmp253;
	wire xformtmp292;
	assign xformtmp292 = ~xformtmp294;
	wire xformtmp302;
	assign xformtmp302 = xformtmp288 & xformtmp292;
	wire xformtmp303;
	assign xformtmp303 = xformtmp302 & xformtmp160783;
	wire xformtmp304;
	assign xformtmp304 = xformtmp303 & xformtmp241;
	assign out[5] = ~xformtmp304;
	wire xformtmp296;
	assign xformtmp296 = xformtmp261 & xformtmp145716;
	wire xformtmp297;
	assign xformtmp297 = xformtmp296 & xformtmp130648;
	wire xformtmp298;
	assign xformtmp298 = xformtmp297 & xformtmp160783;
	wire xformtmp295;
	assign xformtmp295 = ~xformtmp298;
	wire xformtmp305;
	assign xformtmp305 = xformtmp295 & xformtmp288;
	wire xformtmp306;
	assign xformtmp306 = xformtmp305 & xformtmp286;
	wire xformtmp307;
	assign xformtmp307 = xformtmp306 & xformtmp241;
	assign out[6] = ~xformtmp307;
endmodule

module tb();
    reg[6:0] results[1];
    reg[35:0] data[1];
    dut duttest(results[0], data[0]);
    initial begin
        $readmemb("data.txt", data);
        $display("data = [%36b]", data[0]);
        #1
        $display("results = [%7b]", results[0]);
        $writememb("results.txt", results);
    end
endmodule

