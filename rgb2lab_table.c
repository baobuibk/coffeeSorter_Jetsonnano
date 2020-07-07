/*
 * rgb2lab_table.c
 *
 *  Created on: Oct 30, 2019
 *      Author: ducan
 */
#include "rgb2lab_table.h"
const double rgb2xyz_table1[256] = {
		 0.000833805108617456,  0.000983676774575282,  0.001148187872729033,  0.001327720782571499,
		 0.001522643805367888,  0.001733312467678872,  0.001960070639325657,  0.002203251500498892,
		 0.002463178384824831,  0.002740165519395424,  0.003034518678424957,  0.003346535763899161,
		 0.003676507324047436,  0.004024717018496307,  0.004391442037410293,  0.004776953480693729,
		 0.005181516702338386,  0.005605391624202722,  0.006048833022857055,  0.006512090792594474,
		 0.006995410187265387,  0.007499032043226175,  0.008023192985384994,  0.008568125618069307,
		 0.009134058702220787,  0.009721217320237847,  0.010329823029626936,  0.010960094006488246,
		 0.011612245179743887,  0.012286488356915870,  0.012983032342173012,  0.013702083047289686,
		 0.014443843596092545,  0.015208514422912709,  0.015996293365509631,  0.016807375752887384,
		 0.017641954488384078,  0.018500220128379697,  0.019382360956935723,  0.020288563056652401,
		 0.021219010376003558,  0.022173884793387381,  0.023153366178110410,  0.024157632448504756,
		 0.025186859627361627,  0.026241221894849898,  0.027320891639074897,  0.028426039504420793,
		 0.029556834437808800,  0.030713443732993635,  0.031896033073011532,  0.033104766570885055,
		 0.034339806808682170,  0.035601314875020343,  0.036889450401100039,  0.038204371595346502,
		 0.039546235276732830,  0.040915196906853191,  0.042311410620809675,  0.043735029256973465,
		 0.045186204385675541,  0.046665086336880102,  0.048171824226889426,  0.049706565984127232,
		 0.051269458374043238,  0.052860647023180246,  0.054480276442442369,  0.056128490049600091,
		 0.057805430191067229,  0.059511238162981199,  0.061246054231617608,  0.063010017653167674,
		 0.064803266692905773,  0.066625938643772892,  0.068478169844400166,  0.070360095696595876,
		 0.072271850682317479,  0.074213568380149628,  0.076185381481307851,  0.078187421805186341,
		 0.080219820314468310,  0.082282707129814794,  0.084376211544148816,  0.086500462036549763,
		 0.088655586285772942,  0.090841711183407670,  0.093058962846687465,  0.095307466630964705,
		 0.097587347141862457,  0.099898728247113891,  0.102241733088101305,  0.104616484091104189,
		 0.107023102978267615,  0.109461710778299331,  0.111932427836905601,  0.114435373826973746,
		 0.116970667758510838,  0.119538427988345616,  0.122138772229601872,  0.124771817560950488,
		 0.127437680435647432,  0.130136476690364294,  0.132868321553817975,  0.135633329655205664,
		 0.138431615032451827,  0.141263291140271641,  0.144128470858057772,  0.147027266497594983,
		 0.149959789810608562,  0.152926151996150173,  0.155926463707827395,  0.158960835060880407,
		 0.162029375639110990,  0.165132194501667606,  0.168269400189690749,  0.171441100732822593,
		 0.174647403655585037,  0.177888415983629145,  0.181164244249860218,  0.184474994500440997,
		 0.187820772300677868,  0.191201682740791412,  0.194617830441575823,  0.198069319559948859,
		 0.201556253794397067,  0.205078736390316929,  0.208636870145255754,  0.212230757414055227,
		 0.215860500113899234,  0.219526199729269234,  0.223227957316808501,  0.226965873510098365,
		 0.230740048524349151,  0.234550582161005217,  0.238397573812271002,  0.242281122465554860,
		 0.246201326707835483,  0.250158284729953440,  0.254152094330826750,  0.258182852921595818,
		 0.262250657529696229,  0.266355604802862467,  0.270497791013065814,  0.274677312060384649,
		 0.278894263476810400,  0.283148740429992107,  0.287440837726917475,  0.291770649817535865,
		 0.296138270798321113,  0.300543794415776500,  0.304987314069886273,  0.309468922817508540,
		 0.313988713375717543,  0.318546778125091856,  0.323143209112950747,  0.327778098056542178,
		 0.332451536346179355,  0.337163615048330367,  0.341914424908660974,  0.346704056355029600,
		 0.351532599500439358,  0.356400144145943509,  0.361306779783509502,  0.366252595598839492,
		 0.371237680474149123,  0.376262122990906445,  0.381326011432530088,  0.386429433787049026,
		 0.391572477749723258,  0.396755230725626851,  0.401977779832195736,  0.407240211901736704,
		 0.412542613483903753,  0.417885070848137474,  0.423267669986071682,  0.428690496613906680,
		 0.434153636174748891,  0.439657173840918791,  0.445201194516227861,  0.450785782838223459,
		 0.456411023180404662,  0.462076999654407072,  0.467783796112158978,  0.473531496148009545,
		 0.479320183100826802,  0.485149940056070372,  0.491020849847835616,  0.496932995060870408,
		 0.502886458032568706,  0.508881320854933761,  0.514917665376521394,  0.520995573204354301,
		 0.527115125705813092,  0.533276404010505245,  0.539479489012107072,  0.545724461370186598,
		 0.552011401512000122,  0.558340389634267908,  0.564711505704929229,  0.571124829464873085,
		 0.577580440429650621,  0.584078417891164103,  0.590618840919336918,  0.597201788363763364,
		 0.603827338855337792,  0.610495570807864762,  0.617206562419651106,  0.623960391675076109,
		 0.630757136346146829,  0.637596873994032642,  0.644479681970582141,  0.651405637419824157,
		 0.658374817279448576,  0.665387298282272055,  0.672443156957687527,  0.679542469633093837,
		 0.686685312435313500,  0.693871761291989908,  0.701101891932973120,  0.708375779891686763,
		 0.715693500506480729,  0.723055128921969326,  0.730460740090353555,  0.737910408772730841,
		 0.745404209540387441,  0.752942216776077866,  0.760524504675292423,  0.768151147247507105,
		 0.775822218317423595,  0.783537791526193517,  0.791297940332630234,  0.799102738014409009,
		 0.806952257669251605,  0.814846572216101239,  0.822785754396283542,  0.830769876774654636,
		 0.838799011740740008,  0.846873231509858049,  0.854992608124233833,  0.863157213454102346,
		 0.871367119198797280,  0.879622396887831726,  0.887923117881966317,  0.896269353374266387,
		 0.904661174391149570,  0.913098651793419203,  0.921581856277294609,  0.930110858375423732,
		 0.938685728457888002,  0.947306536733199867,  0.955973353249286117,  0.964686247894465110,
		 0.973445290398412544,  0.982250550333117145,  0.991102097113829794,  1.000000000000000000
};

//================================================================================================
const double rgb2xyz_table2[256]={
		 0.000000000000000000,  0.000303526983548838,  0.000607053967097675,  0.000910580950646512,
		 0.001214107934195350,  0.001517634917744187,  0.001821161901293025,  0.002124688884841863,
		 0.002428215868390700,  0.002731742851939537,  0.003035269835488375,  0.003338796819037212,
		 0.003642323802586050,  0.003945850786134887,  0.004249377769683725,  0.004552904753232562,
		 0.004856431736781400,  0.005159958720330237,  0.005463485703879075,  0.005767012687427913,
		 0.006070539670976750,  0.006374066654525588,  0.006677593638074425,  0.006981120621623262,
		 0.007284647605172100,  0.007588174588720937,  0.007891701572269774,  0.008195228555818612,
		 0.008498755539367450,  0.008802282522916286,  0.009105809506465124,  0.009409336490013962,
		 0.009712863473562800,  0.010016390457111638,  0.010319917440660475,  0.010623444424209313,
		 0.010926971407758149,  0.011230498391306989,  0.011534025374855825,  0.011837552358404663,
		 0.012141079341953499,  0.012444606325502337,  0.012748133309051175,  0.013051660292600013,
		 0.013355187276148850,  0.013658714259697688,  0.013962241243246524,  0.014265768226795364,
		 0.014569295210344200,  0.014872822193893038,  0.015176349177441874,  0.015479876160990714,
		 0.015783403144539548,  0.016086930128088386,  0.016390457111637224,  0.016693984095186062,
		 0.016997511078734900,  0.017301038062283738,  0.017604565045832573,  0.017908092029381414,
		 0.018211619012930249,  0.018515145996479087,  0.018818672980027925,  0.019122199963576763,
		 0.019425726947125601,  0.019729253930674436,  0.020032780914223277,  0.020336307897772112,
		 0.020639834881320950,  0.020943361864869784,  0.021246888848418626,  0.021550415831967464,
		 0.021853942815516298,  0.022157469799065136,  0.022460996782613978,  0.022764523766162812,
		 0.023068050749711650,  0.023371577733260485,  0.023675104716809326,  0.023978631700358164,
		 0.024282158683906999,  0.024585685667455837,  0.024889212651004675,  0.025192739634553513,
		 0.025496266618102351,  0.025799793601651185,  0.026103320585200027,  0.026406847568748861,
		 0.026710374552297699,  0.027013901535846537,  0.027317428519395375,  0.027620955502944213,
		 0.027924482486493048,  0.028228009470041886,  0.028531536453590727,  0.028835063437139562,
		 0.029138590420688400,  0.029442117404237234,  0.029745644387786076,  0.030049171371334914,
		 0.030352698354883748,  0.030656225338432586,  0.030959752321981428,  0.031263279305530266,
		 0.031566806289079097,  0.031870333272627935,  0.032173860256176773,  0.032477387239725611,
		 0.032780914223274449,  0.033084441206823287,  0.033387968190372125,  0.033691495173920963,
		 0.033995022157469801,  0.034298549141018632,  0.034602076124567477,  0.034905603108116315,
		 0.035209130091665146,  0.035512657075213984,  0.035816184058762829,  0.036119711042311660,
		 0.036423238025860498,  0.036726765009409336,  0.037030291992958174,  0.037333818976507012,
		 0.037637345960055850,  0.037940872943604688,  0.038244399927153526,  0.038547926910702364,
		 0.038851453894251202,  0.039154980877800033,  0.039458507861348871,  0.039762034844897709,
		 0.040065561828446554,  0.040369088811995392,  0.040672615795544223,  0.040976142779093061,
		 0.041279669762641899,  0.041583196746190737,  0.041886723729739568,  0.042190250713288406,
		 0.042493777696837251,  0.042797304680386089,  0.043100831663934927,  0.043404358647483765,
		 0.043707885631032596,  0.044011412614581434,  0.044314939598130272,  0.044618466581679110,
		 0.044921993565227955,  0.045225520548776786,  0.045529047532325624,  0.045832574515874462,
		 0.046136101499423300,  0.046439628482972138,  0.046743155466520969,  0.047046682450069807,
		 0.047350209433618652,  0.047653736417167490,  0.047957263400716328,  0.048260790384265159,
		 0.048564317367813997,  0.048867844351362835,  0.049171371334911673,  0.049474898318460504,
		 0.049778425302009349,  0.050081952285558187,  0.050385479269107025,  0.050689006252655863,
		 0.050992533236204701,  0.051296060219753532,  0.051599587203302370,  0.051903114186851208,
		 0.052206641170400053,  0.052510168153948891,  0.052813695137497722,  0.053117222121046560,
		 0.053420749104595398,  0.053724276088144236,  0.054027803071693074,  0.054331330055241905,
		 0.054634857038790750,  0.054938384022339588,  0.055241911005888426,  0.055545437989437264,
		 0.055848964972986095,  0.056152491956534933,  0.056456018940083771,  0.056759545923632609,
		 0.057063072907181454,  0.057366599890730285,  0.057670126874279123,  0.057973653857827961,
		 0.058277180841376799,  0.058580707824925637,  0.058884234808474469,  0.059187761792023307,
		 0.059491288775572151,  0.059794815759120989,  0.060098342742669827,  0.060401869726218659,
		 0.060705396709767497,  0.061008923693316335,  0.061312450676865173,  0.061615977660414011,
		 0.061919504643962855,  0.062223031627511687,  0.062526558611060531,  0.062830085594609356,
		 0.063133612578158194,  0.063437139561707032,  0.063740666545255870,  0.064044193528804708,
		 0.064347720512353546,  0.064651247495902384,  0.064954774479451222,  0.065258301463000060,
		 0.065561828446548898,  0.065865355430097736,  0.066168882413646574,  0.066472409397195412,
		 0.066775936380744250,  0.067079463364293088,  0.067382990347841926,  0.067686517331390764,
		 0.067990044314939602,  0.068293571298488440,  0.068597098282037264,  0.068900625265586102,
		 0.069204152249134954,  0.069507679232683792,  0.069811206216232630,  0.070114733199781468,
		 0.070418260183330292,  0.070721787166879130,  0.071025314150427968,  0.071328841133976806,
		 0.071632368117525658,  0.071935895101074482,  0.072239422084623320,  0.072542949068172158,
		 0.072846476051720996,  0.073150003035269834,  0.073453530018818672,  0.073757057002367510,
		 0.074060583985916348,  0.074364110969465186,  0.074667637953014024,  0.074971164936562862,
		 0.075274691920111700,  0.075578218903660538,  0.075881745887209376,  0.076185272870758200,
		 0.076488799854307052,  0.076792326837855890,  0.077095853821404728,  0.077399380804953566
};
//================================================================================================


