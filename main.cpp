#include "ofApp.h"
#include "ofMain.h"


/*


																			   .........
															   ....',;;::cccllllllllllllllccc::;,'...
														 ..',:cllooodxxxxxxdddddddddddddddddxxxxxddoolc:,',.
													..,:clodddxxdddoollcc:;;;,,''''...''',,;;::cclloddxxxdolc:,..              ...,;::::;.
											   ..,:loddddddoolc:;,'..',,..                       ...'cdlclodxxxdoc;'.      .';clodxxxddxxc.
								  ...........,:lddddxdooc:,...  ..,:loddc.                         .cl,   ..';:lodxxol;'';lodxxdolcoxdodo;.
							 ..,:cllooooolllodddddol:,..     .':lddddoodl.                       .cxl.          ..,:ldxxxddddoc,..;odddo,.
						  .':lodxxxdddxdoodddddoc;..       ...,:coddooodc.             ..      .ckx,                 .':lodxxl,..:dddd:.
						.;ldddddoc:,,cddodddo:,..               .:ddooodc.             .:,....cO0c.                      .;cdxdlodxdl,.
					  .:oddddo:'.   'lxddo:,.....               .:ddooodc.              'dxxkOXO:.            ...           .:dkxdo;.
					.;oddddo;.     .;ddc;....'''.               .:ddooodc.         ..'';ckNWWWXxc,.     ..',::,..           .cxxdc'.
				  .'ldddddc'.      .;;,,,:codc'.  ...',;:;;'.   .cddooodc.     ..';cooooxKWWW0o;,'...,:clodxxl,.       ..',coxxxoc,.
				 .;oddodd:.       .';cloddxxl;,,;:cloddddddoc.  .cdooooxl,,,;cloodddddodkOOkOo..,clodddddodxxo:.....,:looddddoooddo;.
				.:ddooddc.        ..;dxdoddl:cloddxdooooooodd;. .cdooooxocllooodxdooooooddc;',;cxddooodddoooddc....':llodxdooooooddc.
			   .cddoooxo'.          .cxdodxl,.':loxdooooooodd;. .cdoooodl'..'coddooddoooodc. .;odooddoodolllod;.    ..:looloddollodc.
			  .colcccloc.          .;loccclo:',locccoddoccclo;. .co::::oc...;oc::clddc::clc. .cl:;:ooccc:;;:lc.     .,lc;;cldo:;;:l:.......
			 .:l:,,,,;cl,.     ..,:cc:,,,,,:l::l:,,;lllc;,,:l:.';ol,,,,lc..,cl;,,clc:;,,;lc',:oc;,,:c:;;:ccc;.      .:l:,,llll;,,;lc;:c;'.
			.'lc,,,,,,;cc:;;;;:ccc:;,,,,,,,,:lol;,,',:c:,,,;ll:;;lc,,,,lc.':lc,:xKk:',,,;clloxdc,;:cc:;cl:,....     .cl,,,:lc:,,,;:lodl'.
			.;lc,,,,,,,,;::::::;;,,,,,,,,,;:clxo,'..'.',,,,,,,''',;,,,,:c:::ccd0Ol,,;;,,,:ll::cccccoo::ol:::::::;'..,lc,,,,,,;:;,,:cc,.
			.,lc,,,,,,,,,,,,,,:c:,,,,,;:ccc::;cc,'.'',:lc:,,,''..cc,,,,l0NX00K0o;,:cll::cc;......':olcclolc;;;::ccc;:l:,;;ccccolccc,.
			 .:l:,,,,,,,,;;:ccodc,;:ccc:;'.. .:xOo,;::;:cclOO:. .cl:;lONMMMMMWO:;::,,:cc,.      .',;,;:odoclc;,,,;cl::c:::;,..,::,.
			  .;ccccccccccc:;;lolcc:;'..    .l00l'...  ..:kx;. .;;:lONWMMMMMMW0:.    ...         . ..:odl,':l:,,,,;lc....
				.',;;;,'.....,:c;'.       .c0Nk,  .   .. .,...l0XkkXWMMMMMWNKl.                   .;cooc,,;ll;,,,,:l;.
							...         .:ONWWKd:dOdcdOxld0kdkXWWNXWMMMWWXd:'                  ..;cccll:ccc:;,,,;cl;.
									  .;kNWWWWWWWWWWWWWWWWWN0ocdklcdKWMNx,                    .:lc:;odlc:;,,,,;cl:'.
									 .oKOkKKdd0Kxd0NWWWWWWKo;,',,,,:OWWXo.     ...            'lc,,;::;,,,,,:cl:'.
									  ,,. ..  ..  'lxoldKN0l;;lc,',c0WWXd'    .''.            .cc,,,,,,,,;clc;..
												 .''''',oXWN0KKo,,,;xXO:. .,cd;.              .cl;,,,,;:cc:,.
												.',,,,ckXWMMMMKo;;o0WNk,.:kK0o.               .cl,,;:ccc,.
												 ....'xNWMMMWWNXKKWWWNx'.,::'                 .coccc:,..
													 .cKWWWWXxcckNMMWNx,.                     .:l:,.
													'd0kccdd:'''cKMMMNk,        ...           ...
												   .lkc.  .'',''cONWWNk,     ...'.
														  .',,'. .oXWWO;  ..:kd'
															...  .dNWW0l';kKKx,
																 .cKWMMWXKko;.
																 .cKWMMWO:.
																  ;0WW0c.
																 .c00l.
																  ,:.

*/
//========================================================================
int main() {
  ofSetupOpenGL(1100, 1000, OF_WINDOW);  // <-------- setup the GL context

  ofRunApp(new ofApp());
}