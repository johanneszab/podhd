#include "mainwindow.h"
#include "ui_mainwindow.h"

QDir presetDirectory; // Path for Preset Directory
QDir backupPath; // Patch for Backup Directory

qint8 presetsPatched; // Counts files patched
qint8 presetsModified; // Counts files moved

// Constants

const QStringList h5eFilter = QStringList() << "*.h5e";
const QStringList h5bFilter = QStringList() << "*.h5b";
const QStringList h5sFilter = QStringList() << "*.h5s";

const QStringList hbeFilter = QStringList() << "*.hbe";
const QStringList hbbFilter = QStringList() << "*.hbb";
const QStringList hbsFilter = QStringList() << "*.hbs";

const QStringList h5eExtension = QStringList() << ".h5e";
const QStringList h5bExtension = QStringList() << ".h5b";
const QStringList h5sExtension = QStringList() << ".h5s";

const QStringList hbeExtension = QStringList() << ".hbe";
const QStringList hbbExtension = QStringList() << ".hbb";
const QStringList hbsExtension = QStringList() << ".hbs";

const QStringList h3eExtension = QStringList() << ".h3e";
const QStringList h4eExtension = QStringList() << ".h4e";
const QStringList h3bExtension = QStringList() << ".h3b";
const QStringList h4bExtension = QStringList() << ".h4b";
const QStringList h3sExtension = QStringList() << ".h3s";
const QStringList h4sExtension = QStringList() << ".h4s";

const QStringList hreFilter = QStringList() << "*.hre";
const QStringList hrbFilter = QStringList() << "*.hrb";
const QStringList hrsFilter = QStringList() << "*.hrs";

const QStringList hreExtension = QStringList() << ".hre";
const QStringList hrbExtension = QStringList() << ".hrb";
const QStringList hrsExtension = QStringList() << ".hrs";

const QStringList sDesktopInputOne = QStringList() << "Guitar" << "Mic";
const QStringList sDesktopInputTwo = QStringList() << "Same" << "Guitar" << "Mic";
const QStringList sDesktopGuitarIn = QStringList() << "Auto" << "22k" << "32k" << "70k" << "90k" << "136k" << "320k" << "1M" << "3.5M";

const QStringList s500InputOne = QStringList() << "Guitar" << "Mic" << "Aux" << "Guitar+Aux" << "Guitar+Variax" << "Gtr+Aux+Variax" << "Variax" << "Variax Mags";
const QStringList s500InputTwo = QStringList() << "Same" << "Guitar" << "Mic" << "Aux" << "Guitar+Aux" << "Guitar+Variax" << "Gtr+Aux+Variax" << "Variax" << "Variax Mags";
const QStringList s500GuitarIn = QStringList() << "Auto" << "22k" << "32k" << "70k" << "90k" << "136k" << "320k" << "1M" << "3.5M";

const QStringList sProInputOne = QStringList() << "Guitar" << "Guitar+Variax" << "Variax" << "Variax+Mags" << "Line L" << "Line R" << "Guitar+Line L"
                                               << "Guitar+Line R" << "Gtr+Line L+Var" << "Gtr+Line R+Var" << "Mic" << "SPDIF L" << "SPDIF R" << "AES L" << "AES R";
const QStringList sProInputTwo = QStringList() << "Same" << "Guitar" << "Guitar+Variax" << "Variax" << "Variax+Mags" << "Line L" << "Line R" << "Guitar+Line L"
                                               << "Guitar+Line R" << "Gtr+Line L+Var" << "Gtr+Line R+Var" << "Mic" << "SPDIF L" << "SPDIF R" << "AES L" << "AES R";
const QStringList sProGuitarIn = QStringList() << "Auto" << "22k" << "32k" << "70k" << "90k" << "136k" << "320k" << "1M" << "3.5M";

const QStringList sAmp = QStringList() << "Blackface Dbl Nrm" << "Blackface Dbl Vib" << "Highway 100" << "Super O" << "Gibtone 185" << "Tweet B-Man Nrm" << "Tweet B-Man Brt"
                                       << "Blackface 'Lux Nrm" << "Blackface 'Lux Vib" << "Divide 9/15" << "PhD Motorway" << "Class A-15" << "Class A-30 TB" << "Brit J-45 Nrm"
                                       << "Brit J-45 Brt" << "Plexi Lead 100 Nrm" << "Plexi Lead 100 Brt" << "Brit P-75 Nrm" << "Brit P-75 Brt" << "Brit J-800" << "Bomber Uber"
                                       << "Treadplate" << "Angel F-Ball" << "Line 6 Elektrik" << "Solo 100 Clean" << "Solo 100 Crunch" << "Solo 100 Overdrive" << "Line 6 Doom"
                                       << "Line 6 Epic" << "Flip Top" << "Blackface Dbl Nrm Pre" << "Blackface Dbl Vib Pre" << "Highway 100 Pre" << "Super O Pre" << "Gibtone 185 Pre"
                                       << "Tweet B-Man Nrm Pre" << "Tweet B-Man Brt Pre" << "Blackface 'Lux Nrm Pre" << "Blackface 'Lux Vib Pre" << "Divide 9/15 Pre"
                                       << "PhD Motorway Pre" << "Class A-15 Pre" << "Class A-30 TB Pre" << "Brit J-45 Nrm Pre" << "Brit J-45 Brt Pre" << "Plexi Lead 100 Nrm Pre"
                                       << "Plexi Lead 100 Brt Pre" << "Brit P-75 Nrm Pre" << "Brit P-75 Brt Pre" << "Brit J-800 Pre" << "Bomber Uber Pre" << "Treadplate Pre"
                                       << "Angel F-Ball Pre" << "Line 6 Elektrik Pre" << "Solo 100 Clean Pre" << "Solo 100 Crunch Pre" << "Solo 100 Overdrive Pre"
                                       << "Line 6 Doom Pre" << "Line 6 Epic Pre" << "Flip Top Pre";
const QStringList sCab = QStringList() << "2x12 PhD Ported" << "1x(6x9) Super O" << "1x12 Celest 12-H" << "1x12 Blackface 'Lux" << "1x12 Gibtone F-Coll" << "1x12 Blue Bell"
                                       << "2x12 Blackface Dbl" << "2x12 Silver Bell" << "4x10 Tweed B-Man" << "4x12 Uber" << "4x12 XXL V-30" << "4x12 Highway" << "4x12 Greenback 25"
                                       << "4x12 Blackback 30" << "4x12 Tread V-30" << "4x12 Brit T-75" << "115 Flip Flop" << "No Cab";
const QStringList sMic = QStringList() << "57 On Axis" << "57 Off Axis" << "409 Dynamic" << "421 Dynamic" << "4038 Ribbon" << "121 Ribbon" << "67 Condenser" << "87 Condenser";

// HD 300 Mapping
const QStringList sFx1300 = QStringList() << "Screamer" << "Tube Drive" << "Classic Distortion" << "Heavy Distortion" << "Color Drive" << "Overdrive" << "Line 6 Drive"
                                          << "Line 6 Distortion" << "Boost Comp" << "Red Comp" << "Blue Comp" << "Vetta Comp" << "Fuzz Pi" << "Octave Fuzz" << "Jet Fuzz" << "Sub Octave Fuzz"
                                          << "Facial Fuzz" << "Jumbo Fuzz" << "Spring" << "Parametric EQ" << "4 Band Shift EQ" << "Tron Down" << "Tron Up" << "Q Filter"
                                          << "Ring Modulator" << "Dimension" << "Frequency Shifter" << "Rotary Drum" << "Smart Harmony" << "Pitch Glide" << "Synth String"
                                          << "Growler" << "Synth-O-Matic" << "Bass Octaver" << "V-Tron" << "Vintage Pre" << "Hard Gate";

const QStringList sFx2300 = QStringList() << "Analog Chorus" << "Analog Flanger" << "U-Vibe" << "Phaser" << "Dual Phaser" << "Barberpole Phaser" << "Panned Phaser"
                                          << "Script Phase" << "Pitch Vibrato" << "Seeker" << "Throbber" << "Spin Cycle" << "Obi Wah" << "Voice Box" << "Opto Remolo"
                                          << "Bias Tremolo" << "Pattern Tremolo" << "Panner";

const QStringList sFx3300 = QStringList() << "Digital Delay" << "Digital Delay w/Mod" << "Analog Echo" << "Analog Echo w/Mod" << "Echo Platter" << "Echo Platter Studio"
                                          << "Lo Red Delay" << "Stereo Delay" << "Ping Pong" << "Dynamic Delay" << "Tape Echo" << "Tape Echo Studio" << "Tube Echo"
                                          << "Tube Echo Studio" << "Auto Volume Echo" << "Sweep Echo" << "Sweep Echo Studio" << "Reverse Delay";

const QStringList sReverbSlot300 = QStringList() << "Plate" << "Room" << "Chamber" << "Hall" << "Cave" << "Octo" << "Tile" << "Echo";

const QStringList sWahSlot300 = QStringList() << "Vetta Wah" << "Fassel" << "Chrome" << "Wheeper" << "Conductor" << "Colorful";

const QStringList sEffects300 = sFx1300 + sFx2300 + sFx3300 + sReverbSlot300 + sWahSlot300;

// HD 400 Mapping
const QStringList sFx1400 = QStringList() << "Screamer" << "Tube Drive" << "Classic Distortion" << "Heavy Distortion" << "Color Drive" << "Overdrive" << "Line 6 Drive"
                                          << "Line 6 Distortion" << "Boost Comp" << "Red Comp" << "Blue Comp" << "Blue Comp Treb" << "Vetta Comp" << "Vetta Juice"
                                          << "Fuzz Pi" << "Octave Fuzz" << "Jet Fuzz" << "Sub Octave Fuzz" << "Buzz Saw" << "Facial Fuzz" << "Jumbo Fuzz" << "'63 Spring"
                                          << "Spring" << "Particle Verb" << "Graphic EQ" << "Studio EQ" << "Parametric EQ" << "4 Band Shift EQ" << "Mid Focus EQ"
                                          << "Slow Filter" << "Tron Down" << "Tron Up" << "Q Filter" << "Ring Modulator" << "Dimension" << "Frequency Shifter"
                                          << "Rotary Drum" << "Rotary Drum & Horn" << "Smart Harmony" << "Pitch Glide" << "Attack Synth" << "Synth String"
                                          << "Growler" << "Synth-O-Matic" << "Octisynth" << "Bass Octaver" << "V-Tron" << "Vintage Pre" << "Hard Gate";

const QStringList sFx2400 = QStringList() << "Analog Chorus" << "Analog Flanger" << "U-Vibe" << "Phaser" << "Dual Phaser" << "Barberpole Phaser" << "Panned Phaser"
                                          << "Script Phase" << "Pitch Vibrato" << "Seeker" << "Throbber" << "Spin Cycle" << "Obi Wah" << "Voice Box" << "Opto Remolo"
                                          << "Bias Tremolo" << "Pattern Tremolo" << "Panner";

const QStringList sFx3400 = QStringList() << "Digital Delay" << "Digital Delay w/Mod" << "Analog Echo" << "Analog Echo w/Mod" << "Echo Platter" << "Echo Platter Studio"
                                          << "Lo Res Delay" << "Stereo Delay" << "Ping Pong" << "Dynamic Delay" << "Tape Echo" << "Tape Echo Studio" << "Tube Echo"
                                          << "Tube Echo Studio" << "Multi-Head-Delay" << "Auto Volume Echo" << "Sweep Echo" << "Sweep Echo Studio" << "Reverse Delay";

const QStringList sReverbSlot400 = QStringList() << "Plate" << "Room" << "Chamber" << "Hall" << "Cave" << "Ducking" << "Octo" << "Tile" << "Echo";

const QStringList sWahSlot400 = QStringList() << "Vetta Wah" << "Fassel" << "Chrome" << "Wheeper" << "Conductor" << "Colorful" << "Throaty" << "Chrome Custom";

const QStringList sEffects400 = sFx1400 + sFx2400 + sFx3400 + sReverbSlot400 + sWahSlot400;

char sourceOne[1] = { '\x01' };
char sourceTwo[1] = { '\x00' };
char guitarIn[1] = { '\x00' };

char ampOne[1] = { '\x01' };
char cabOne[1] = { '\x00' };
char micOne[1] = { '\x00' };

char ampTwo[1] = { '\x01' };
char cabTwo[1] = { '\x00' };
char micTwo[1] = { '\x00' };

bool CabOneOff = false, CabTwoOff = false;


// QLists

QList<QCheckBox*> desktopPatchChkbxFive;
QList<QCheckBox*> desktopPatchChkbxPro;
QList<QCheckBox*> desktopModifyChkbx;

QList<QCheckBox*> fivePatchChkbxDesktop;
QList<QCheckBox*> fivePatchChkbxPro;
QList<QCheckBox*> fiveModifyChkbx;

QList<QCheckBox*> proPatchChkbxFive;
QList<QCheckBox*> proPatchChkbxDesktop;
QList<QCheckBox*> proModifyChkbx;

QList<QCheckBox*> translateCheckboxes300;
QList<QCheckBox*> translateCheckboxes400;

QList<QStringList> fileList;

QList<QStringList> fileFilterDesktop;
QList<QStringList> fileFilterPro;
QList<QStringList> fileFilter500;

QList<QStringList> fileExtension500;
QList<QStringList> fileExtension300;
QList<QStringList> fileExtension400;
QList<QStringList> fileExtensionDesktop;
QList<QStringList> fileExtensionPro;

QList<QCheckBox*> listChkbxEditAmp;
QList<QCheckBox*> listChkbxEditCab;
QList<QCheckBox*> listChkbxEditMic;

QList<QComboBox*> listCbEditAmp;
QList<QComboBox*> listCbEditCab;
QList<QComboBox*> listCbEditMic;


// QHashes

QHash<char,char> AmpsToPreAmps;
QHash<char,char> PreAmpsToAmps;

QHash<char,char> InputDesktopTo500;
QHash<char,char> InputDesktopToPro;
QHash<char,char> InputProTo500;
QHash<char,char> InputProToDesktop;
QHash<char,char> Input500ToDesktop;
QHash<char,char> Input500ToPro;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // declare variables

    //sourceOne[0] = '\x01';
    //sourceOne[1] = '\0';

    //sourceTwo[0] = '\x00';
    //sourceTwo[1] = '\0';

    //guitarIn[0] = '\x00';
    //guitarIn[1] = '\0';

    // QComboboxes
    // Input Sources & Guitar In:
    // HD 500

    ui->fiveCbSourceOne->addItems(s500InputOne);
    ui->fiveCbSourceOne->setCurrentIndex(0);
    ui->fiveCbSourceOne->setDisabled(true);

    ui->fiveCbSourceTwo->addItems(s500InputTwo);
    ui->fiveCbSourceTwo->setCurrentIndex(0);
    ui->fiveCbSourceTwo->setDisabled(true);

    ui->fiveCbGuitarInput->addItems(s500GuitarIn);
    ui->fiveCbGuitarInput->setCurrentIndex(0);
    ui->fiveCbGuitarInput->setDisabled(true);

    // HD Desktop

    ui->desktopCbSourceOne->addItems(sDesktopInputOne);
    ui->desktopCbSourceOne->setCurrentIndex(0);
    ui->desktopCbSourceOne->setDisabled(true);

    ui->desktopCbSourceTwo->addItems(sDesktopInputTwo);
    ui->desktopCbSourceTwo->setCurrentIndex(0);
    ui->desktopCbSourceTwo->setDisabled(true);

    ui->desktopCbGuitarInput->addItems(sDesktopGuitarIn);
    ui->desktopCbGuitarInput->setCurrentIndex(0);
    ui->desktopCbGuitarInput->setDisabled(true);

    // HD Pro

    ui->proCbSourceOne->addItems(sProInputOne);
    ui->proCbSourceOne->setCurrentIndex(0);
    ui->proCbSourceOne->setDisabled(true);

    ui->proCbSourceTwo->addItems(sProInputTwo);
    ui->proCbSourceTwo->setCurrentIndex(0);
    ui->proCbSourceTwo->setDisabled(true);

    ui->proCbGuitarInput->addItems(sProGuitarIn);
    ui->proCbGuitarInput->setCurrentIndex(0);
    ui->proCbGuitarInput->setDisabled(true);

    // Modfiy Amps, Cabs and Mics:
    // HD 500

    ui->fiveCbFirstAmp->addItems(sAmp);
    ui->fiveCbFirstAmp->setCurrentIndex(0);
    ui->fiveCbFirstAmp->setDisabled(true);

    ui->fiveCbFirstCab->addItems(sCab);
    ui->fiveCbFirstCab->setCurrentIndex(0);
    ui->fiveCbFirstCab->setDisabled(true);

    ui->fiveCbFirstMic->addItems(sMic);
    ui->fiveCbFirstMic->setCurrentIndex(0);
    ui->fiveCbFirstMic->setDisabled(true);

    ui->fiveCbSecondAmp->addItems(sAmp);
    ui->fiveCbSecondAmp->setCurrentIndex(0);
    ui->fiveCbSecondAmp->setDisabled(true);

    ui->fiveCbSecondCab->addItems(sCab);
    ui->fiveCbSecondCab->setCurrentIndex(0);
    ui->fiveCbSecondCab->setDisabled(true);

    ui->fiveCbSecondMic->addItems(sMic);
    ui->fiveCbSecondMic->setCurrentIndex(0);
    ui->fiveCbSecondMic->setDisabled(true);

    // HD Desktop

    ui->desktopCbFirstAmp->addItems(sAmp);
    ui->desktopCbFirstAmp->setCurrentIndex(0);
    ui->desktopCbFirstAmp->setDisabled(true);

    ui->desktopCbFirstCab->addItems(sCab);
    ui->desktopCbFirstCab->setCurrentIndex(0);
    ui->desktopCbFirstCab->setDisabled(true);

    ui->desktopCbFirstMic->addItems(sMic);
    ui->desktopCbFirstMic->setCurrentIndex(0);
    ui->desktopCbFirstMic->setDisabled(true);

    ui->desktopCbSecondAmp->addItems(sAmp);
    ui->desktopCbSecondAmp->setCurrentIndex(0);
    ui->desktopCbSecondAmp->setDisabled(true);

    ui->desktopCbSecondCab->addItems(sCab);
    ui->desktopCbSecondCab->setCurrentIndex(0);
    ui->desktopCbSecondCab->setDisabled(true);

    ui->desktopCbSecondMic->addItems(sMic);
    ui->desktopCbSecondMic->setCurrentIndex(0);
    ui->desktopCbSecondMic->setDisabled(true);

    // HD Pro

    ui->proCbFirstAmp->addItems(sAmp);
    ui->proCbFirstAmp->setCurrentIndex(0);
    ui->proCbFirstAmp->setDisabled(true);

    ui->proCbFirstCab->addItems(sCab);
    ui->proCbFirstCab->setCurrentIndex(0);
    ui->proCbFirstCab->setDisabled(true);

    ui->proCbFirstMic->addItems(sMic);
    ui->proCbFirstMic->setCurrentIndex(0);
    ui->proCbFirstMic->setDisabled(true);

    ui->proCbSecondAmp->addItems(sAmp);
    ui->proCbSecondAmp->setCurrentIndex(0);
    ui->proCbSecondAmp->setDisabled(true);

    ui->proCbSecondCab->addItems(sCab);
    ui->proCbSecondCab->setCurrentIndex(0);
    ui->proCbSecondCab->setDisabled(true);

    ui->proCbSecondMic->addItems(sMic);
    ui->proCbSecondMic->setCurrentIndex(0);
    ui->proCbSecondMic->setDisabled(true);

    // HD 300

    ui->threePg3CbTubeComp->addItems(sEffects300);
    ui->threePg3CbTubeComp->setCurrentIndex(9);
    ui->threePg3CbBlueComp->addItems(sEffects300);
    ui->threePg3CbBlueComp->setCurrentIndex(10);
    ui->threePg3CbVettaJuice->addItems(sEffects300);
    ui->threePg3CbVettaJuice->setCurrentIndex(11);

    ui->threePg3CbBuzzSaw->addItems(sEffects300);
    ui->threePg3CbBuzzSaw->setCurrentIndex(14);

    ui->threePg3CbTriChorus->addItems(sEffects300);
    ui->threePg3CbTriChorus->setCurrentIndex(37);
    ui->threePg3CbJetFlanger->addItems(sEffects300);
    ui->threePg3CbJetFlanger->setCurrentIndex(38);
    ui->threePg3CbACFlanger->addItems(sEffects300);
    ui->threePg3CbACFlanger->setCurrentIndex(38);
    ui->threePg3Cb80AFlanger->addItems(sEffects300);
    ui->threePg3Cb80AFlanger->setCurrentIndex(38);
    ui->threePg3CbRotaryDrum->addItems(sEffects300);
    ui->threePg3CbRotaryDrum->setCurrentIndex(27);

    ui->threePg3CbVocoder->addItems(sEffects300);
    ui->threePg3CbVocoder->setCurrentIndex(46);
    ui->threePg3CbSlowFilter->addItems(sEffects300);
    ui->threePg3CbSlowFilter->setCurrentIndex(47);
    ui->threePg3CbCometTrails->addItems(sEffects300);
    ui->threePg3CbCometTrails->setCurrentIndex(48);
    ui->threePg3CbOctiSynth->addItems(sEffects300);
    ui->threePg3CbOctiSynth->setCurrentIndex(48);
    ui->threePg3CbAttackSynth->addItems(sEffects300);
    ui->threePg3CbAttackSynth->setCurrentIndex(30);

    ui->threePg3CbGraphicEQ->addItems(sEffects300);
    ui->threePg3CbGraphicEQ->setCurrentIndex(19);
    ui->threePg3CbStudioEQ->addItems(sEffects300);
    ui->threePg3CbStudioEQ->setCurrentIndex(20);
    ui->threePg3CbMidFocusEQ->addItems(sEffects300);
    ui->threePg3CbMidFocusEQ->setCurrentIndex(20);

    ui->threePg3CbMultiHeadDelay->addItems(sEffects300);
    ui->threePg3CbMultiHeadDelay->setCurrentIndex(55);

    ui->threePg3CbDucking->addItems(sEffects300);
    ui->threePg3CbDucking->setCurrentIndex(77);
    ui->threePg3Cb63Spring->addItems(sEffects300);
    ui->threePg3Cb63Spring->setCurrentIndex(18);
    ui->threePg3CbParticleVerb->addItems(sEffects300);
    ui->threePg3CbParticleVerb->setCurrentIndex(18);


    ui->threePg3CbThroaty->addItems(sEffects300);
    ui->threePg3CbThroaty->setCurrentIndex(85);
    ui->threePg3CbChromeCustom->addItems(sEffects300);
    ui->threePg3CbChromeCustom->setCurrentIndex(83);


    // HD 400
    ui->threePg4CbTubeComp->addItems(sEffects400);
    ui->threePg4CbTubeComp->setCurrentIndex(9);

    ui->threePg4CbTriChorus->addItems(sEffects400);
    ui->threePg4CbTriChorus->setCurrentIndex(49);
    ui->threePg4CbJetFlanger->addItems(sEffects400);
    ui->threePg4CbJetFlanger->setCurrentIndex(50);
    ui->threePg4CbACFlanger->addItems(sEffects400);
    ui->threePg4CbACFlanger->setCurrentIndex(50);
    ui->threePg4Cb80AFlanger->addItems(sEffects400);
    ui->threePg4Cb80AFlanger->setCurrentIndex(50);

    ui->threePg4CbVocoder->addItems(sEffects400);
    ui->threePg4CbVocoder->setCurrentIndex(58);
    ui->threePg4CbCometTrails->addItems(sEffects400);
    ui->threePg4CbCometTrails->setCurrentIndex(60);


    // Generate QLists:

    // Placeholder

    QStringList FilesOne;
    QStringList FilesTwo;
    QStringList FilesThree;
    QStringList FilesFour;
    QStringList FilesFive;
    QStringList FilesSix;

    //fileList
    fileList.append(FilesOne);
    fileList.append(FilesTwo);
    fileList.append(FilesThree);

    // Generate QLists for Checkboxes
    //HD Desktop
    desktopPatchChkbxFive.append(ui->desktopChkbxPatchH5e);
    desktopPatchChkbxFive.append(ui->desktopChkbxPatchH5b);
    desktopPatchChkbxFive.append(ui->desktopChkbxPatchH5s);
    desktopPatchChkbxPro.append(ui->desktopChkbxPatchHre);
    desktopPatchChkbxPro.append(ui->desktopChkbxPatchHrb);
    desktopPatchChkbxPro.append(ui->desktopChkbxPatchHrs);

    desktopModifyChkbx.append(ui->desktopChkbxModifyHbe);
    desktopModifyChkbx.append(ui->desktopChkbxModifyHbb);
    desktopModifyChkbx.append(ui->desktopChkbxModifyHbs);

    // HD 500
    fivePatchChkbxDesktop.append(ui->fiveChkbxPatchHbe);
    fivePatchChkbxDesktop.append(ui->fiveChkbxPatchHbb);
    fivePatchChkbxDesktop.append(ui->fiveChkbxPatchHbs);
    fivePatchChkbxPro.append(ui->fiveChkbxPatchHre);
    fivePatchChkbxPro.append(ui->fiveChkbxPatchHrb);
    fivePatchChkbxPro.append(ui->fiveChkbxPatchHrs);

    fiveModifyChkbx.append(ui->fiveChkbxModifyH5e);
    fiveModifyChkbx.append(ui->fiveChkbxModifyH5b);
    fiveModifyChkbx.append(ui->fiveChkbxModifyH5s);

    //HD 300 / 400
    translateCheckboxes300.append(ui->threeChkbxPatchH3e);
    //translateCheckboxes300.append(ui->threeChkbxPatchH3b);
    //translateCheckboxes300.append(ui->threeChkbxPatchH3s);

    translateCheckboxes400.append(ui->threeChkbxPatchH4e);
    //translateCheckboxes400.append(ui->threeChkbxPatchH4b);
    //translateCheckboxes400.append(ui->threeChkbxPatchH4s);


    //HD Pro
    proPatchChkbxFive.append(ui->proChkbxPatchH5e);
    proPatchChkbxFive.append(ui->proChkbxPatchH5b);
    proPatchChkbxFive.append(ui->proChkbxPatchH5s);
    proPatchChkbxDesktop.append(ui->proChkbxPatchHbe);
    proPatchChkbxDesktop.append(ui->proChkbxPatchHbb);
    proPatchChkbxDesktop.append(ui->proChkbxPatchHbs);

    proModifyChkbx.append(ui->proChkbxModifyHre);
    proModifyChkbx.append(ui->proChkbxModifyHrb);
    proModifyChkbx.append(ui->proChkbxModifyHrs);

    //fileFilters
    // HD 500
    fileFilter500.append(h5eFilter);
    fileFilter500.append(h5bFilter);
    fileFilter500.append(h5sFilter);

    // HD Destktop
    fileFilterDesktop.append(hbeFilter);
    fileFilterDesktop.append(hbbFilter);
    fileFilterDesktop.append(hbsFilter);

    // HD Pro
    fileFilterPro.append(hreFilter);
    fileFilterPro.append(hrbFilter);
    fileFilterPro.append(hrsFilter);

    //fileExtensions
    // HD Desktop
    fileExtensionDesktop.append(hbeExtension);
    fileExtensionDesktop.append(hbbExtension);
    fileExtensionDesktop.append(hbsExtension);

    // HD Pro
    fileExtensionPro.append(hreExtension);
    fileExtensionPro.append(hrbExtension);
    fileExtensionPro.append(hrsExtension);

    // HD 500
    fileExtension500.append(h5eExtension);
    fileExtension500.append(h5bExtension);
    fileExtension500.append(h5sExtension);

    // HD 300
    fileExtension300.append(h3eExtension);
    fileExtension300.append(h3bExtension);
    fileExtension300.append(h3sExtension);

    // HD 400
    fileExtension400.append(h4eExtension);
    fileExtension400.append(h4bExtension);
    fileExtension400.append(h4sExtension);


    // Process Amp, Cab, Mic QLists
    // CheckBoxes

    listChkbxEditAmp.append(ui->fiveChkbxEditFirstAmp);
    listChkbxEditAmp.append(ui->desktopChkbxEditFirstAmp);
    listChkbxEditAmp.append(ui->proChkbxEditFirstAmp);

    listChkbxEditCab.append(ui->fiveChkbxEditFirstCab);
    listChkbxEditCab.append(ui->desktopChkbxEditFirstCab);
    listChkbxEditCab.append(ui->proChkbxEditFirstCab);

    listChkbxEditMic.append(ui->fiveChkbxEditFirstMic);
    listChkbxEditMic.append(ui->desktopChkbxEditFirstMic);
    listChkbxEditMic.append(ui->proChkbxEditFirstMic);

    listChkbxEditAmp.append(ui->fiveChkbxEditSecondAmp);
    listChkbxEditAmp.append(ui->desktopChkbxEditSecondAmp);
    listChkbxEditAmp.append(ui->proChkbxEditSecondAmp);

    listChkbxEditCab.append(ui->fiveChkbxEditSecondCab);
    listChkbxEditCab.append(ui->desktopChkbxEditSecondCab);
    listChkbxEditCab.append(ui->proChkbxEditSecondCab);

    listChkbxEditMic.append(ui->fiveChkbxEditSecondMic);
    listChkbxEditMic.append(ui->desktopChkbxEditSecondMic);
    listChkbxEditMic.append(ui->proChkbxEditSecondMic);

    // ComboBoxes
    listCbEditAmp.append(ui->fiveCbFirstAmp);
    listCbEditAmp.append(ui->desktopCbFirstAmp);
    listCbEditAmp.append(ui->proCbFirstAmp);

    listCbEditCab.append(ui->fiveCbFirstCab);
    listCbEditCab.append(ui->desktopCbFirstCab);
    listCbEditCab.append(ui->proCbFirstCab);

    listCbEditMic.append(ui->fiveCbFirstMic);
    listCbEditMic.append(ui->desktopCbFirstMic);
    listCbEditMic.append(ui->proCbFirstMic);

    listCbEditAmp.append(ui->fiveCbSecondAmp);
    listCbEditAmp.append(ui->desktopCbSecondAmp);
    listCbEditAmp.append(ui->proCbSecondAmp);

    listCbEditCab.append(ui->fiveCbSecondCab);
    listCbEditCab.append(ui->desktopCbSecondCab);
    listCbEditCab.append(ui->proCbSecondCab);

    listCbEditMic.append(ui->fiveCbSecondMic);
    listCbEditMic.append(ui->desktopCbSecondMic);
    listCbEditMic.append(ui->proCbSecondMic);

    // Generate QHashes

    // Amp Models
    AmpsToPreAmps.insert(0x05, 0x20);
    AmpsToPreAmps.insert(0x06, 0x21);
    AmpsToPreAmps.insert(0x08, 0x23);
    AmpsToPreAmps.insert(0x0E, 0x29);
    AmpsToPreAmps.insert(0x14, 0x2F);
    AmpsToPreAmps.insert(0x01, 0x1C);
    AmpsToPreAmps.insert(0x02, 0x1D);
    AmpsToPreAmps.insert(0x03, 0x1E);
    AmpsToPreAmps.insert(0x04, 0x1F);
    AmpsToPreAmps.insert(0x12, 0x2D);
    AmpsToPreAmps.insert(0x00, 0x1B);
    AmpsToPreAmps.insert(0x10, 0x2B);
    AmpsToPreAmps.insert(0x11, 0x2C);
    AmpsToPreAmps.insert(0x09, 0x24);
    AmpsToPreAmps.insert(0x0A, 0x25);
    AmpsToPreAmps.insert(0x55, 0x56);
    AmpsToPreAmps.insert(0x58, 0x59);
    AmpsToPreAmps.insert(0x0C, 0x27);
    AmpsToPreAmps.insert(0x0D, 0x28);
    AmpsToPreAmps.insert(0x15, 0x30);
    AmpsToPreAmps.insert(0x17, 0x32);
    AmpsToPreAmps.insert(0x0B, 0x26);
    AmpsToPreAmps.insert(0x19, 0x34);
    AmpsToPreAmps.insert(0x52, 0x53);
    AmpsToPreAmps.insert(0x5E, 0x5F);
    AmpsToPreAmps.insert(0x61, 0x62);
    AmpsToPreAmps.insert(0x64, 0x65);
    AmpsToPreAmps.insert(0x67, 0x68);
    AmpsToPreAmps.insert(0x6A, 0x6B);
    AmpsToPreAmps.insert(0x5B, 0x5C);

    // Pre Models
    PreAmpsToAmps.insert(0x20, 0x05);
    PreAmpsToAmps.insert(0x21, 0x06);
    PreAmpsToAmps.insert(0x23, 0x08);
    PreAmpsToAmps.insert(0x29, 0x0E);
    PreAmpsToAmps.insert(0x2F, 0x14);
    PreAmpsToAmps.insert(0x1C, 0x01);
    PreAmpsToAmps.insert(0x1D, 0x02);
    PreAmpsToAmps.insert(0x1E, 0x03);
    PreAmpsToAmps.insert(0x1F, 0x04);
    PreAmpsToAmps.insert(0x2D, 0x12);
    PreAmpsToAmps.insert(0x1B, 0x00);
    PreAmpsToAmps.insert(0x2B, 0x10);
    PreAmpsToAmps.insert(0x2C, 0x11);
    PreAmpsToAmps.insert(0x24, 0x09);
    PreAmpsToAmps.insert(0x25, 0x0A);
    PreAmpsToAmps.insert(0x56, 0x55);
    PreAmpsToAmps.insert(0x59, 0x58);
    PreAmpsToAmps.insert(0x27, 0x0C);
    PreAmpsToAmps.insert(0x28, 0x0D);
    PreAmpsToAmps.insert(0x30, 0x15);
    PreAmpsToAmps.insert(0x32, 0x17);
    PreAmpsToAmps.insert(0x26, 0x0B);
    PreAmpsToAmps.insert(0x34, 0x19);
    PreAmpsToAmps.insert(0x53, 0x52);
    PreAmpsToAmps.insert(0x5F, 0x5E);
    PreAmpsToAmps.insert(0x62, 0x61);
    PreAmpsToAmps.insert(0x65, 0x64);
    PreAmpsToAmps.insert(0x68, 0x67);
    PreAmpsToAmps.insert(0x6B, 0x6A);
    PreAmpsToAmps.insert(0x5C, 0x5B);

    Input500ToDesktop.insert(0x00, 0x00);
    Input500ToDesktop.insert(0x01, 0x01);
    Input500ToDesktop.insert(0x02, 0x02);

    Input500ToPro.insert(0x00, 0x00);
    Input500ToPro.insert(0x01, 0x01);
    Input500ToPro.insert(0x02, 0x0C);
    //Input500ToPro.insert(0x03, 0x); // Aux
    //Input500ToPro.insert(0x05, 0x); // Guitar+Aux
    Input500ToPro.insert(0x06, 0x03);
    //Input500ToPro.insert(0x07, 0x); // Gtr+Aux+Variax
    Input500ToPro.insert(0x08, 0x04);
    Input500ToPro.insert(0x09, 0x05);

    InputDesktopTo500.insert(0x00, 0x00);
    InputDesktopTo500.insert(0x01, 0x01);
    InputDesktopTo500.insert(0x02, 0x02);

    InputDesktopToPro.insert(0x00, 0x00);
    InputDesktopTo500.insert(0x01, 0x01);
    InputDesktopToPro.insert(0x02, 0x0C);

    InputProTo500.insert(0x00, 0x00);
    InputProTo500.insert(0x01, 0x01);
    InputProTo500.insert(0x03, 0x06);
    InputProTo500.insert(0x04, 0x08);
    InputProTo500.insert(0x05, 0x09);
    //InputProTo500.insert(0x06, 0x);
    //InputProTo500.insert(0x07, 0x);
    //InputProTo500.insert(0x09, 0x);
    //InputProTo500.insert(0x0A, 0x);
    //InputProTo500.insert(0x0B, 0x);
    InputProTo500.insert(0x0C, 0x02);
    //InputProTo500.insert(0x0D, 0x);
    //InputProTo500.insert(0x0E, 0x);
    //InputProTo500.insert(0x0F, 0x);
    //InputProTo500.insert(0x10, 0x);

    InputProToDesktop.insert(0x00, 0x00);
    InputProToDesktop.insert(0x01, 0x01);
    //InputProToDesktop.insert(0x03, 0x06);
    //InputProToDesktop.insert(0x04, 0x08);
    //åInputProToDesktop.insert(0x05, 0x09);
    //InputProToDesktop.insert(0x06, 0x);
    //InputProToDesktop.insert(0x07, 0x);
    //InputProToDesktop.insert(0x09, 0x);
    //InputProToDesktop.insert(0x0A, 0x);
    //InputProToDesktop.insert(0x0B, 0x);
    InputProToDesktop.insert(0x0C, 0x02);
    //InputProToDesktop.insert(0x0D, 0x);
    //InputProToDesktop.insert(0x0E, 0x);
    //InputProToDesktop.insert(0x0F, 0x);
    //InputProToDesktop.insert(0x10, 0x);

    // signals/slots mechanism in action

    connect( ui->actionOpen, SIGNAL( triggered() ), this, SLOT( getPath() ) );
    connect( ui->actionAbout, SIGNAL( triggered() ), this, SLOT( openDialogAbout() ) );
    connect( ui->actionClose, SIGNAL( triggered() ), this, SLOT( close() ) );

    // HD Desktop
    connect( ui->desktopBtnBrowse, SIGNAL( clicked() ), this, SLOT( getPath() ) );
    connect( ui->desktopBtnRun, SIGNAL( clicked() ), this, SLOT( runDesktop() ) );
    connect( ui->desktopLeDirectoryChoser, SIGNAL( textEdited(QString) ), this, SLOT( onTextEdit(QString) ) );

    connect( ui->desktopChkbxEditFirstAmp, SIGNAL(clicked(bool)), ui->desktopCbFirstAmp, SLOT(setEnabled(bool)) );
    connect( ui->desktopChkbxEditFirstCab, SIGNAL(clicked(bool)), ui->desktopCbFirstCab, SLOT(setEnabled(bool)) );
    connect( ui->desktopChkbxEditFirstMic, SIGNAL(clicked(bool)), ui->desktopCbFirstMic, SLOT(setEnabled(bool)) );

    connect( ui->desktopChkbxEditSecondAmp, SIGNAL(clicked(bool)), ui->desktopCbSecondAmp, SLOT(setEnabled(bool)) );
    connect( ui->desktopChkbxEditSecondCab, SIGNAL(clicked(bool)), ui->desktopCbSecondCab, SLOT(setEnabled(bool)) );
    connect( ui->desktopChkbxEditSecondMic, SIGNAL(clicked(bool)), ui->desktopCbSecondMic, SLOT(setEnabled(bool)) );

    connect( ui->desktopChkbxEditInputs, SIGNAL(clicked(bool)), ui->desktopCbSourceOne, SLOT(setEnabled(bool)) );
    connect( ui->desktopChkbxEditInputs, SIGNAL(clicked(bool)), ui->desktopCbSourceTwo, SLOT(setEnabled(bool)) );
    connect( ui->desktopChkbxEditInputs, SIGNAL(clicked(bool)), ui->desktopCbGuitarInput, SLOT(setEnabled(bool)) );

    // HD 300
    connect( ui->threeBtnbrowse, SIGNAL( clicked() ), this, SLOT( getPath() ) );
    connect( ui->threeBtnRun, SIGNAL( clicked() ), this, SLOT( run300() ) );
    connect( ui->threeLeDirectoryChoser, SIGNAL( textEdited(QString) ), this, SLOT( onTextEdit(QString) ) );

    //Switch QStackedWidget
    connect( ui->threeChkbxPatchH3e, SIGNAL( clicked() ), this, SLOT(changePage300()) );
    connect( ui->threeChkbxPatchH4e, SIGNAL( clicked() ), this, SLOT(changePage400()) );


    // HD 500
    connect( ui->fiveBtnBrowse, SIGNAL( clicked() ), this, SLOT( getPath() ) );
    connect( ui->fiveBtnRun, SIGNAL( clicked() ), this, SLOT( run500() ) );
    connect( ui->fiveLeDirectoryChoser, SIGNAL( textEdited(QString) ), this, SLOT( onTextEdit(QString) ) );

    connect( ui->fiveChkbxEditFirstAmp, SIGNAL(clicked(bool)), ui->fiveCbFirstAmp, SLOT(setEnabled(bool)) );
    connect( ui->fiveChkbxEditFirstCab, SIGNAL(clicked(bool)), ui->fiveCbFirstCab, SLOT(setEnabled(bool)) );
    connect( ui->fiveChkbxEditFirstMic, SIGNAL(clicked(bool)), ui->fiveCbFirstMic, SLOT(setEnabled(bool)) );

    connect( ui->fiveChkbxEditSecondAmp, SIGNAL(clicked(bool)), ui->fiveCbSecondAmp, SLOT(setEnabled(bool)) );
    connect( ui->fiveChkbxEditSecondCab, SIGNAL(clicked(bool)), ui->fiveCbSecondCab, SLOT(setEnabled(bool)) );
    connect( ui->fiveChkbxEditSecondMic, SIGNAL(clicked(bool)), ui->fiveCbSecondMic, SLOT(setEnabled(bool)) );

    connect( ui->fiveChkbxEditInputs, SIGNAL(clicked(bool)), ui->fiveCbSourceOne, SLOT(setEnabled(bool)) );
    connect( ui->fiveChkbxEditInputs, SIGNAL(clicked(bool)), ui->fiveCbSourceTwo, SLOT(setEnabled(bool)) );
    connect( ui->fiveChkbxEditInputs, SIGNAL(clicked(bool)), ui->fiveCbGuitarInput, SLOT(setEnabled(bool)) );

    // HD Pro
    connect( ui->proBtnBrowse, SIGNAL( clicked() ), this, SLOT( getPath() ) );
    connect( ui->proBtnRun, SIGNAL( clicked() ), this, SLOT( runPro() ) );
    connect( ui->proLeDirectoryChoser, SIGNAL( textEdited(QString) ), this, SLOT( onTextEdit(QString) ) );

    connect( ui->proChkbxEditFirstAmp, SIGNAL(clicked(bool)), ui->proCbFirstAmp, SLOT(setEnabled(bool)) );
    connect( ui->proChkbxEditFirstCab, SIGNAL(clicked(bool)), ui->proCbFirstCab, SLOT(setEnabled(bool)) );
    connect( ui->proChkbxEditFirstMic, SIGNAL(clicked(bool)), ui->proCbFirstMic, SLOT(setEnabled(bool)) );

    connect( ui->proChkbxEditSecondAmp, SIGNAL(clicked(bool)), ui->proCbSecondAmp, SLOT(setEnabled(bool)) );
    connect( ui->proChkbxEditSecondCab, SIGNAL(clicked(bool)), ui->proCbSecondCab, SLOT(setEnabled(bool)) );
    connect( ui->proChkbxEditSecondMic, SIGNAL(clicked(bool)), ui->proCbSecondMic, SLOT(setEnabled(bool)) );

    connect( ui->proChkbxEditInputs, SIGNAL(clicked(bool)), ui->proCbSourceOne, SLOT(setEnabled(bool)) );
    connect( ui->proChkbxEditInputs, SIGNAL(clicked(bool)), ui->proCbSourceTwo, SLOT(setEnabled(bool)) );
    connect( ui->proChkbxEditInputs, SIGNAL(clicked(bool)), ui->proCbGuitarInput, SLOT(setEnabled(bool)) );

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::openDialogAbout() {
//    dialogAbout ad(this);
//    ad.exec();
//}

void MainWindow::openDialogAbout() {
    dialogAbout* adialog = new dialogAbout;
    adialog->setAttribute(Qt::WA_DeleteOnClose);
    adialog->show();
}

void MainWindow::changePage300() {

    //int nextPage = ui->threeStackedWidget->currentIndex() + 1;
    //if (nextPage >= ui->threeStackedWidget->count())
    //   nextPage = 0;
    //ui->threeStackedWidget->setCurrentIndex(nextPage);

    ui->threeStackedWidget->setCurrentIndex(1);
}

void MainWindow::changePage400() {

    ui->threeStackedWidget->setCurrentIndex(2);
}

void MainWindow::getPath() {

    QString path;

    path = QFileDialog::getExistingDirectory(this, tr("Select Directory with Preset Files"), presetDirectory.path(), QFileDialog::ShowDirsOnly);
    if ( path.isNull() == false )
    {
        presetDirectory.setPath(path);
    }
    ui->fiveLeDirectoryChoser->setText(path);
    ui->desktopLeDirectoryChoser->setText(path);
    ui->proLeDirectoryChoser->setText(path);
    ui->threeLeDirectoryChoser->setText(path);
}

void MainWindow::onTextEdit(QString path) {
    // get path from QLineEdit (le_directoryChoser)
    //path = ui->le_directoryChoser->text();

    if ( path.isNull() == false )
    {
        presetDirectory.setPath(path);
    }
}

bool MainWindow::getFiles(QDir dir, QList<QStringList> fileFilter) {

    bool error = false;
    // Clear Files

    for (int i = 0; i < fileList.size(); i++) {
        fileList[i].clear();
    }

    // Get Files

    QStringList tmpFiles;
    for (int i = 0; i < fileFilter.size(); i++) {
        dir.setNameFilters(fileFilter.at(i));
        QStringList tmpList = dir.entryList(QDir::Files|QDir::Readable);
        for (QStringList::const_iterator it=tmpList.constBegin(); it!=tmpList.constEnd(); ++it) {
            //qDebug() << dir.absoluteFilePath(*it);
            //fileList.replace(i,QStringList() << dir.absoluteFilePath(*it));
            tmpFiles << dir.absoluteFilePath(*it);

        }
        //qDebug() << tmpFiles;
        fileList.replace(i, tmpFiles);
        //qDebug() << "test" << fileList[i];
        tmpFiles.clear();

    }
    return !error;
}

void MainWindow::copyModify() {
    if (ui->desktopChkbxBackup->isChecked()) {
        for (int i = 0; i < desktopModifyChkbx.size(); i++) {
             if (desktopModifyChkbx.at(i)->isChecked() ) {
                 copyFiles(presetDirectory, fileList.at(i), true);
             }
        }
    }
    if (ui->fiveChkbxBackup->isChecked()) {
        for (int i = 0; i < fiveModifyChkbx.size(); i++) {
             if (fiveModifyChkbx.at(i)->isChecked() ) {
                 copyFiles(presetDirectory, fileList.at(i), true);
             }
        }
    }
    if (ui->proChkbxBackup->isChecked()) {
        for (int i = 0; i < proModifyChkbx.size(); i++) {
             if (proModifyChkbx.at(i)->isChecked() ) {
                 copyFiles(presetDirectory, fileList.at(i), true);
             }
        }
    }
    if (ui->threeChkbxBackup->isChecked()) {
        for (int i = 0; i < translateCheckboxes400.size(); i++) {
             if (translateCheckboxes300.at(i)->isChecked() ) {
                 copyFiles(presetDirectory, fileList.at(i), true);
             }
        }
    }
    if (ui->threeChkbxBackup->isChecked()) {
        for (int i = 0; i < translateCheckboxes300.size(); i++) {
             if (translateCheckboxes300.at(i)->isChecked() ) {
                 copyFiles(presetDirectory, fileList.at(i), true);
             }
        }
    }
}


void MainWindow::copyConvert(QList<QCheckBox*> chkbx) {

    if (ui->desktopChkbxBackup->isChecked()) {
        for (int i = 0; i < chkbx.size(); i++) {
             if (chkbx.at(i)->isChecked() ) {
                 copyFiles(presetDirectory, fileList.at(i), true);
             }
        }
    }

    if (ui->fiveChkbxBackup->isChecked()) {
        for (int i = 0; i < chkbx.size(); i++) {
             if (chkbx.at(i)->isChecked() ) {
                 copyFiles(presetDirectory, fileList.at(i), true);
             }
        }
    }

    if (ui->proChkbxBackup->isChecked()) {
        for (int i = 0; i < chkbx.size(); i++) {
             if (chkbx.at(i)->isChecked() ) {
                 copyFiles(presetDirectory, fileList.at(i), true);
             }
        }
    }
}

bool MainWindow::copyFiles(QDir source, QStringList files, const bool override) {
        //QDir directory(source);
        bool error = false;
        QString destination = source.path() + QDir::separator() + "backup";

        if (!source.exists()) {
            return false;
        }

        //QStringList dirs = source.entryList(QDir::AllDirs | QDir::Hidden);
        //QStringList files = source.entryList(QDir::Files | QDir::Hidden);

        QList<QString>::iterator f; // add d for directoy traversal

        //for (d = dirs.begin(); d != dirs.end(); ++d) {
        //    if ((*d) == "." || (*d) == "..") {
        //        continue;
        //    }
#ifdef QT_DEBUG
        //    std::cout<< "copyDir dir name " <<(*d).toStdString() << std::endl;
#endif
        //    if (!QFileInfo(source.path() + "/" + (*d)).isDir()) {
        //        files << (*d);
        //        continue;
        //    }

        //    QDir temp(destination + "/" + (*d));
        //    temp.mkpath(temp.path());

        //    if (!copyDir(source.path() + "/" + (*d), destination + "/" + (*d), override)) {
#ifdef QT_DEBUG
        //        std::cout << "copyDir err: "<< (source.path() + "/" + (*d), destination + "/" + (*d)).toStdString() << std::endl;
#endif
        //        error = true;
        //    }
        //}

        QDir temp(destination + QDir::separator());
        temp.mkpath(temp.path());

        for (f = files.begin(); f != files.end(); ++f) {
            QFile tempFile((*f));
            QFile destFile(destination + QDir::separator() + source.relativeFilePath(tempFile.fileName()));

            if (destFile.exists() && override) {
                destFile.remove();
            }

            if (!tempFile.copy(destination + QDir::separator() + source.relativeFilePath(tempFile.fileName()))) {
#ifdef QT_DEBUG
                std::cout << "copyDir err: "<< (destination + QDir::separator() + source.relativeFilePath(tempFile.fileName())).toStdString() << std::endl;
#endif
                error = true;

            }
        }
    return !error;
}

void MainWindow::rename(QList<QCheckBox*> chkbx, QString pressedFrom) {

    if (pressedFrom.compare("Desktop") == 0) {

        for (int i = 0; i < chkbx.size(); i++) {
            if (chkbx.at(i)->isChecked() ) {
                renameFiles(presetDirectory, fileList.at(i), fileExtensionDesktop.at(i));
            }
        }
    } else if (pressedFrom.compare("Pro") == 0) {

        for (int i = 0; i < chkbx.size(); i++) {
            if (chkbx.at(i)->isChecked() ) {
                renameFiles(presetDirectory, fileList.at(i), fileExtensionPro.at(i));
            }
        }
    } else if (pressedFrom.compare("500") == 0) {

        for (int i = 0; i < chkbx.size(); i++) {
            if (chkbx.at(i)->isChecked() ) {
                renameFiles(presetDirectory, fileList.at(i), fileExtension500.at(i));
            }
        }
    }
}

bool MainWindow::renameFiles(QDir source, QStringList files, QStringList extension) {

    bool error = false;

    QList<QString>::iterator f; // add d for directoy traversal

    for (f = files.begin(); f != files.end(); ++f) {
        QFileInfo tempFile((*f));
        QString newname = tempFile.baseName() + extension[0];

        if (!source.rename((*f), newname)) {
#ifdef QT_DEBUG
            std::cout << "renameFiles err: "<< ((*f), newname).toStdString() << std::endl;
#endif
            error = true;

        }
    }
    return !error;
}

void MainWindow::changeTextDesktop() {
    ui->desktopLbAfterRun->setText("");

    QString StringDone;
    //QString StringPatched = StringPatched.setNum(presetsPatched);
    //QString StringMoved = StringMoved.setNum(presetsMoved);

    if (ui->desktopChkbxBackup->isChecked()) {
        StringDone = QString("Done: %1 files patched and renamed. Backup created.").arg(presetsPatched);
    } else {
        StringDone = QString("Done: %1 files patched and renamed.").arg(presetsPatched);
    }

    if (ui->desktopChkbxModifyHbe->isChecked() || ui->desktopChkbxModifyHbb->isChecked() || ui->desktopChkbxModifyHbs->isChecked()) {
        if (ui->desktopChkbxBackup->isChecked()) {
            StringDone = QString("Done: %1 files edited. Backup created.").arg(presetsModified);
        } else {
            StringDone = QString("Done: %1 files edited.").arg(presetsModified);
        }
    }

    ui->desktopLbAfterRun->setText(StringDone);
}

void MainWindow::changeText300() {
    ui->threeLbAfterRun->setText("");

    QString StringDone;

    if (ui->threeChkbxBackup->isChecked()) {
        StringDone = QString("Done: %1 files translated. Backup created.").arg(presetsPatched);
    } else {
        StringDone = QString("Done: %1 files translated.").arg(presetsPatched);
    }

    ui->threeLbAfterRun->setText(StringDone);
}

void MainWindow::changeText500() {
    ui->fiveLbAfterRun->setText("");

    QString StringDone;

    if (ui->fiveChkbxBackup->isChecked()) {
        StringDone = QString("Done: %1 files patched and renamed. Backup created.").arg(presetsPatched);
    } else {
        StringDone = QString("Done: %1 files patched and renamed.").arg(presetsPatched);
    }

    if (ui->fiveChkbxModifyH5e->isChecked() || ui->fiveChkbxModifyH5b->isChecked() || ui->fiveChkbxModifyH5s->isChecked())  {
        if (ui->fiveChkbxBackup->isChecked()) {
            StringDone = QString("Done: %1 files edited. Backup created.").arg(presetsModified);
        } else {
            StringDone = QString("Done: %1 files edited.").arg(presetsModified);
        }
    }

    ui->fiveLbAfterRun->setText(StringDone);
}

void MainWindow::changeTextPro() {
    ui->proLbAfterRun->setText("");

    QString StringDone;

    if (ui->proChkbxBackup->isChecked()) {
        StringDone = QString("Done: %1 files patched and renamed. Backup created.").arg(presetsPatched);
    } else {
        StringDone = QString("Done: %1 files patched and renamed.").arg(presetsPatched);
    }

    if (ui->proChkbxModifyHre->isChecked() || ui->proChkbxModifyHrb->isChecked() || ui->proChkbxModifyHrs->isChecked()) {
        if (ui->proChkbxBackup->isChecked()) {
            StringDone = QString("Done: %1 files edited. Backup created.").arg(presetsModified);
        } else {
            StringDone = QString("Done: %1 files edited.").arg(presetsModified);
        }
    }

    ui->proLbAfterRun->setText(StringDone);
}

void MainWindow::convert(QString pressedFrom) {

    //presetsPatched = 0;

    //for (int i = 0; i < patchCheckboxes.size(); i++) {
    //    if (patchCheckboxes.at(i)->isChecked() ) {
    //        convertPresetFiles(fileList.at(i));
    //        presetsPatched = presetsPatched + fileList.at(i).count();
    //    }
    //}

    if (pressedFrom.compare("Desktop") == 0) {
        //if (ui->desktopChkbxPatchH5e->isChecked()) {
            convertPresetFiles(fileList.at(0), "Desktop");
                presetsPatched = presetsPatched + fileList.at(0).count();
                //release h5eFiles
        //}
        //if (ui->desktopChkbxPatchH5b->isChecked()) {
            convertBundleFiles(fileList.at(1), "Desktop");
                presetsPatched = presetsPatched + fileList.at(1).count();
                //release hbeFiles
        //}
        //if (ui->desktopChkbxPatchH5s->isChecked()) {
            convertSetlistFiles(fileList.at(2), "Desktop");
                presetsPatched = presetsPatched + fileList.at(2).count();
                //release hbeFiles
        //}
        //if (ui->desktopChkbxModifyHbe->isChecked()) {
        //        modifyPresetFiles(fileList.at(0));
        //        presetsPatched = fileList.at(0).count();
        //        //release h5eFiles
        //}
    } else if (pressedFrom.compare("300") == 0) {
        if (ui->threeChkbxPatchH3e->isChecked()) {
                translatePresetFiles(presetDirectory, fileList.at(0), fileExtension300.at(0), true);
                presetsPatched = presetsPatched + fileList.at(0).count();
                //release h5eFiles
        }
        if (ui->threeChkbxPatchH4e->isChecked()) {
                translatePresetFiles(presetDirectory, fileList.at(0), fileExtension400.at(0), true);
                presetsPatched = presetsPatched + fileList.at(0).count();
                //release hbeFiles
        }
    } else if (pressedFrom.compare("500") == 0) {
        //if (ui->fiveChkbxPatchHbe->isChecked()) {
            convertPresetFiles(fileList.at(0), "500");
                presetsPatched = presetsPatched + fileList.at(0).count();
                //release h5eFiles
        //}
        //if (ui->fiveChkbxPatchHbb->isChecked()) {
            convertBundleFiles(fileList.at(1), "500");
                presetsPatched = presetsPatched + fileList.at(1).count();
                //release hbeFiles
        //}
        //if (ui->fiveChkbxPatchHbs->isChecked()) {
            convertSetlistFiles(fileList.at(2), "500");
                presetsPatched = presetsPatched + fileList.at(2).count();
                //release hbeFiles
        //}
        //if (ui->fiveChkbxModifyH5e->isChecked()) {
        //        modifyPresetFiles(fileList.at(0));
        //        presetsPatched = fileList.at(0).count();
        //        //release h5eFiles
        //}
    } else if (pressedFrom.compare("Pro") == 0) {
        //if (ui->proChkbxPatchH5e->isChecked()) {
            convertPresetFiles(fileList.at(0), "Pro");
                presetsPatched = presetsPatched + fileList.at(0).count();
                //release h5eFiles
        //}
        //if (ui->proChkbxPatchH5b->isChecked()) {
            convertBundleFiles(fileList.at(1), "Pro");
                presetsPatched = presetsPatched + fileList.at(1).count();
                //release hbeFiles
        //}
        //if (ui->proChkbxPatchH5s->isChecked()) {
            convertSetlistFiles(fileList.at(2), "Pro");
                presetsPatched = presetsPatched + fileList.at(2).count();
                //release hbeFiles
        //}
        //if (ui->proChkbxModifyHre->isChecked()) {
        //        modifyPresetFiles(fileList.at(0));
        //        presetsPatched = fileList.at(0).count();
        //        //release h5eFiles
        //}
    }}

void MainWindow::modify(QString pressedFrom) {

    //presetsModified = 0;

    if (pressedFrom.compare("Desktop") == 0) {
        if (ui->desktopChkbxModifyHbe->isChecked()) {

            convertPresetFiles(fileList.at(0), "Desktop");
            presetsModified = presetsModified + fileList.at(0).count();
            modifyPresetFiles(fileList.at(0));
        }
        if (ui->desktopChkbxModifyHbb->isChecked()) {

            convertBundleFiles(fileList.at(1), "Desktop");
            presetsModified = presetsModified + fileList.at(1).count();
            modifyBundleFiles(fileList.at(1));
        }
        if (ui->desktopChkbxModifyHbs->isChecked()) {

            convertSetlistFiles(fileList.at(2), "Desktop");
            presetsModified = presetsModified + fileList.at(2).count();
            modifySetlistFiles(fileList.at(2));
        }
    } else if (pressedFrom.compare("500") == 0) {
        if (ui->fiveChkbxModifyH5e->isChecked()) {
            convertPresetFiles(fileList.at(0), "500");
            modifyPresetFiles(fileList.at(0));
            presetsModified = presetsModified + fileList.at(0).count();
        }
        if (ui->fiveChkbxModifyH5b->isChecked()) {

            convertBundleFiles(fileList.at(1), "500");
            presetsModified = presetsModified + fileList.at(1).count();
            modifyBundleFiles(fileList.at(1));
        }
        if (ui->fiveChkbxModifyH5s->isChecked()) {

            convertSetlistFiles(fileList.at(2), "500");
            presetsModified = presetsModified + fileList.at(2).count();
            modifySetlistFiles(fileList.at(2));
        }
    } else if (pressedFrom.compare("Pro") == 0) {

        if (ui->proChkbxModifyHre->isChecked()) {
            convertPresetFiles(fileList.at(0), "Pro");
            modifyPresetFiles(fileList.at(0));
            presetsModified = presetsModified + fileList.at(0).count();
        }
        if (ui->proChkbxModifyHrb->isChecked()) {

            convertBundleFiles(fileList.at(1), "Pro");
            presetsModified = presetsModified + fileList.at(1).count();
            modifyBundleFiles(fileList.at(1));
        }
        if (ui->proChkbxModifyHrs->isChecked()) {

            convertSetlistFiles(fileList.at(2), "Pro");
            presetsModified = presetsModified + fileList.at(2).count();
            modifySetlistFiles(fileList.at(2));
        }
    }
}

void MainWindow::changeAmps(QString pressedFrom) {

    //presetsModified = 0;

    if (pressedFrom.compare("Desktop") == 0) {
        if (ui->desktopChkbxModifyHbe->isChecked()) {

            if (ui->desktopChkbxEditAmpToPre->isChecked())  {
                changePresetFilesAmps(AmpsToPreAmps, fileList.at(0));
            } else if (ui->desktopChkbxEditPreToAmp->isChecked())  {
                changePresetFilesAmps(PreAmpsToAmps, fileList.at(0));
            }
            //presetsModified = presetsModified + fileList.at(0).count();

        }
        if (ui->desktopChkbxModifyHbb->isChecked()) {

            if (ui->desktopChkbxEditAmpToPre->isChecked())  {
                changeBundleFilesAmps(AmpsToPreAmps, fileList.at(1));
            } else if (ui->desktopChkbxEditPreToAmp->isChecked())  {
                changeBundleFilesAmps(PreAmpsToAmps, fileList.at(1));
            }
            //presetsModified = presetsModified + fileList.at(1).count();
        }
        if (ui->desktopChkbxModifyHbs->isChecked()) {

            if (ui->desktopChkbxEditAmpToPre->isChecked())  {
                changeSetlistFilesAmps(AmpsToPreAmps, fileList.at(2));
            } else if (ui->desktopChkbxEditPreToAmp->isChecked())  {
                changeSetlistFilesAmps(PreAmpsToAmps, fileList.at(2));
            }
            //presetsModified = presetsModified + fileList.at(2).count();
        }
    } else if (pressedFrom.compare("500") == 0) {
        if (ui->fiveChkbxModifyH5e->isChecked()) {

            if (ui->fiveChkbxEditAmpToPre->isChecked())  {
                changePresetFilesAmps(AmpsToPreAmps, fileList.at(0));
            } else if (ui->fiveChkbxEditPreToAmp->isChecked())  {
                changePresetFilesAmps(PreAmpsToAmps, fileList.at(0));
            }
            //presetsModified = presetsModified + fileList.at(0).count();
        }
        if (ui->fiveChkbxModifyH5b->isChecked()) {

            if (ui->fiveChkbxEditAmpToPre->isChecked())  {
                changeBundleFilesAmps(AmpsToPreAmps, fileList.at(1));
            } else if (ui->fiveChkbxEditPreToAmp->isChecked())  {
                changeBundleFilesAmps(PreAmpsToAmps, fileList.at(1));
            }

            //presetsModified = presetsModified + fileList.at(1).count();
        }
        if (ui->fiveChkbxModifyH5s->isChecked()) {

            if (ui->fiveChkbxEditAmpToPre->isChecked())  {
                changeSetlistFilesAmps(AmpsToPreAmps, fileList.at(2));
            } else if (ui->fiveChkbxEditPreToAmp->isChecked())  {
                changeSetlistFilesAmps(PreAmpsToAmps, fileList.at(2));
            }
            //presetsModified = presetsModified + fileList.at(2).count();
        }
    } else if (pressedFrom.compare("Pro") == 0) {

        if (ui->proChkbxModifyHre->isChecked()) {

            if (ui->proChkbxEditAmpToPre->isChecked())  {
                changePresetFilesAmps(AmpsToPreAmps, fileList.at(0));
            } else if (ui->proChkbxEditPreToAmp->isChecked())  {
                changePresetFilesAmps(PreAmpsToAmps, fileList.at(0));
            }
            //presetsModified = presetsModified + fileList.at(0).count();
        }
        if (ui->proChkbxModifyHrb->isChecked()) {

            if (ui->proChkbxEditAmpToPre->isChecked())  {
                changeBundleFilesAmps(AmpsToPreAmps, fileList.at(1));
            } else if (ui->proChkbxEditPreToAmp->isChecked())  {
                changeBundleFilesAmps(PreAmpsToAmps, fileList.at(1));
            }
            //presetsModified = presetsModified + fileList.at(1).count();
        }
        if (ui->proChkbxModifyHrs->isChecked()) {

            if (ui->proChkbxEditAmpToPre->isChecked())  {
                changeSetlistFilesAmps(AmpsToPreAmps, fileList.at(2));
            } else if (ui->proChkbxEditPreToAmp->isChecked())  {
                changeSetlistFilesAmps(PreAmpsToAmps, fileList.at(2));
            }
            //presetsModified = presetsModified + fileList.at(2).count();
        }
    }
}

void MainWindow::processSettings(QString pressedFrom) {

    if (pressedFrom.compare("Desktop") == 0) {
        sourceOne[0] = '\x01';
        sourceTwo[0] = '\x00';
        guitarIn[0] = '\x00';
    } else if (pressedFrom.compare("500") == 0) {
        sourceOne[0] = '\x01';
        sourceTwo[0] = '\x08';
        guitarIn[0] = '\x00';
    } else if (pressedFrom.compare("Pro") == 0) {
        sourceOne[0] = '\x01';
        sourceTwo[0] = '\x04';
        guitarIn[0] = '\x00';
    }

    if (ui->desktopChkbxEditInputs->isChecked()) {
        switch (ui->desktopCbSourceOne->currentIndex()) {
            case 0:
                sourceOne[0] = '\x01';
                //sourceOne[1] = '\0';
                break;
            case 1:
                sourceOne[0] = '\x02';
                //sourceOne[1] = '\0';
                break;
        }
        switch (ui->desktopCbSourceTwo->currentIndex()) {
            case 0:
                sourceTwo[0] = '\x00';
                //sourceTwo[1] = '\0';
                break;
            case 1:
                sourceTwo[0] = '\x01';
                //sourceTwo[1] = '\0';
                break;
            case 2:
                sourceTwo[0] = '\x02';
                //sourceTwo[1] = '\0';
        }
        switch (ui->desktopCbGuitarInput->currentIndex()) {
            case 0:
                guitarIn[0] = '\x00';
                //guitarIn[1] = '\0';
                break;
            case 1:
                guitarIn[0] = '\x01';
                //guitarIn[1] = '\0';
                break;
            case 2:
                guitarIn[0] = '\x02';
                //guitarIn[1] = '\0';
            case 3:
                guitarIn[0] = '\x03';
                //guitarIn[1] = '\0';
                break;
            case 4:
                guitarIn[0] = '\x04';
                //guitarIn[1] = '\0';
                break;
            case 5:
                guitarIn[0] = '\x05';
                //guitarIn[1] = '\0';
                break;
            case 6:
                guitarIn[0] = '\x06';
                //guitarIn[1] = '\0';
                break;
            case 7:
                guitarIn[0] = '\x07';
                //guitarIn[1] = '\0';
                break;
            case 8:
                guitarIn[0] = '\x08';
                //guitarIn[1] = '\0';
        }
    }
    if (ui->fiveChkbxEditInputs->isChecked()) {
        switch (ui->fiveCbSourceOne->currentIndex()) {
            case 0:
                sourceOne[0] = '\x01';
                //sourceOne[1] = '\0';
                break;
            case 1:
                sourceOne[0] = '\x02';
                //sourceOne[1] = '\0';
                break;
            case 2:
                sourceOne[0] = '\x03';
                //sourceOne[1] = '\0';
                break;
            case 3:
                sourceOne[0] = '\x05';
                //sourceOne[1] = '\0';
                break;
            case 4:
                sourceOne[0] = '\x06';
                //sourceOne[1] = '\0';
                break;
            case 5:
                sourceOne[0] = '\x07';
                //sourceOne[1] = '\0';
                break;
            case 6:
                sourceOne[0] = '\x08';
                //sourceOne[1] = '\0';
                break;
            case 7:
                sourceOne[0] = '\x09';
                //sourceOne[1] = '\0';
                break;
        }
        switch (ui->fiveCbSourceTwo->currentIndex()) {
            case 0:
                sourceTwo[0] = '\x00';
                //sourceTwo[1] = '\0';
                break;
            case 1:
                sourceTwo[0] = '\x01';
                //sourceTwo[1] = '\0';
                break;
            case 2:
                sourceTwo[0] = '\x02';
                //sourceTwo[1] = '\0';
                break;
            case 3:
                sourceTwo[0] = '\x03';
                //sourceTwo[1] = '\0';
                break;
            case 4:
                sourceTwo[0] = '\x05';
                //sourceTwo[1] = '\0';
                break;
            case 5:
                sourceTwo[0] = '\x06';
                //sourceTwo[1] = '\0';
                break;
            case 6:
                sourceTwo[0] = '\x07';
                //sourceTwo[1] = '\0';
                break;
            case 7:
                sourceTwo[0] = '\x08';
                //sourceTwo[1] = '\0';
                break;
            case 8:
                sourceTwo[0] = '\x09';
                //sourceTwo[1] = '\0';
                break;
        }
        switch (ui->fiveCbGuitarInput->currentIndex()) {
            case 0:
                guitarIn[0] = '\x00';
                //guitarIn[1] = '\0';
                break;
            case 1:
                guitarIn[0] = '\x01';
                //guitarIn[1] = '\0';
                break;
            case 2:
                guitarIn[0] = '\x02';
                //guitarIn[1] = '\0';
                break;
            case 3:
                guitarIn[0] = '\x03';
                //guitarIn[1] = '\0';
                break;
            case 4:
                guitarIn[0] = '\x04';
                //guitarIn[1] = '\0';
                break;
            case 5:
                guitarIn[0] = '\x05';
                //guitarIn[1] = '\0';
                break;
            case 6:
                guitarIn[0] = '\x06';
                //guitarIn[1] = '\0';
                break;
            case 7:
                guitarIn[0] = '\x07';
                //guitarIn[1] = '\0';
                break;
            case 8:
                guitarIn[0] = '\x08';
                //guitarIn[1] = '\0';
                break;
        }
    }
    if (ui->proChkbxEditInputs->isChecked()) {
        switch (ui->proCbSourceOne->currentIndex()) {
            case 0:
                sourceOne[0] = '\x01';
                //sourceOne[1] = '\0';
                break;
            case 1:
                sourceOne[0] = '\x03';
                //sourceOne[1] = '\0';
                break;
            case 2:
                sourceOne[0] = '\x04';
                //sourceOne[1] = '\0';
                break;
            case 3:
                sourceOne[0] = '\x05';
                //sourceOne[1] = '\0';
                break;
            case 4:
                sourceOne[0] = '\x06';
                //sourceOne[1] = '\0';
                break;
            case 5:
                sourceOne[0] = '\x07';
                //sourceOne[1] = '\0';
                break;
            case 6:
                sourceOne[0] = '\x08';
                //sourceOne[1] = '\0';
                break;
            case 7:
                sourceOne[0] = '\x09';
                //sourceOne[1] = '\0';
                break;
            case 8:
                sourceOne[0] = '\x0A';
                //sourceOne[1] = '\0';
                break;
            case 9:
                sourceOne[0] = '\x0B';
                //sourceOne[1] = '\0';
                break;
            case 10:
                sourceOne[0] = '\x0C';
                //sourceOne[1] = '\0';
                break;
            case 11:
                sourceOne[0] = '\x0D';
                //sourceOne[1] = '\0';
                break;
            case 12:
                sourceOne[0] = '\x0E';
                //sourceOne[1] = '\0';
                break;
            case 13:
                sourceOne[0] = '\x0F';
                //sourceOne[1] = '\0';
                break;
            case 14:
                sourceOne[0] = '\x10';
                //sourceOne[1] = '\0';
                break;
        }
        switch (ui->proCbSourceTwo->currentIndex()) {
            case 0:
                sourceTwo[0] = '\x00';
                //sourceTwo[1] = '\0';
                break;
            case 1:
                sourceTwo[0] = '\x01';
                //sourceTwo[1] = '\0';
                break;
            case 2:
                sourceTwo[0] = '\x03';
                //sourceTwo[1] = '\0';
                break;
            case 3:
                sourceTwo[0] = '\x04';
                //sourceTwo[1] = '\0';
                break;
            case 4:
                sourceTwo[0] = '\x05';
                //sourceTwo[1] = '\0';
                break;
            case 5:
                sourceTwo[0] = '\x06';
                //sourceTwo[1] = '\0';
                break;
            case 6:
                sourceTwo[0] = '\x07';
                //sourceTwo[1] = '\0';
                break;
            case 7:
                sourceTwo[0] = '\x08';
                //sourceTwo[1] = '\0';
                break;
            case 8:
                sourceTwo[0] = '\x09';
                //sourceTwo[1] = '\0';
                break;
            case 9:
                sourceTwo[0] = '\x0A';
                //sourceTwo[1] = '\0';
                break;
            case 10:
                sourceTwo[0] = '\x0B';
                //sourceTwo[1] = '\0';
                break;
            case 11:
                sourceTwo[0] = '\x0C';
                //sourceTwo[1] = '\0';
                break;
            case 12:
                sourceTwo[0] = '\x0D';
                //sourceTwo[1] = '\0';
                break;
            case 13:
                sourceTwo[0] = '\x0E';
                //sourceTwo[1] = '\0';
                break;
            case 14:
                sourceTwo[0] = '\x0F';
                //sourceTwo[1] = '\0';
                break;
            case 15:
                sourceTwo[0] = '\x10';
                //sourceTwo[1] = '\0';
                break;
        }
        switch (ui->proCbGuitarInput->currentIndex()) {
            case 0:
                guitarIn[0] = '\x00';
                //guitarIn[1] = '\0';
                break;
            case 1:
                guitarIn[0] = '\x01';
                //guitarIn[1] = '\0';
                break;
            case 2:
                guitarIn[0] = '\x02';
                //guitarIn[1] = '\0';
            case 3:
                guitarIn[0] = '\x03';
                //guitarIn[1] = '\0';
                break;
            case 4:
                guitarIn[0] = '\x04';
                //guitarIn[1] = '\0';
                break;
            case 5:
                guitarIn[0] = '\x05';
                //guitarIn[1] = '\0';
                break;
            case 6:
                guitarIn[0] = '\x06';
                //guitarIn[1] = '\0';
                break;
            case 7:
                guitarIn[0] = '\x07';
                //guitarIn[1] = '\0';
                break;
            case 8:
                guitarIn[0] = '\x08';
                //guitarIn[1] = '\0';
        }
    }

}

void MainWindow::convertPresetFiles(QStringList presetFiles, QString pressedFrom) {

    qint64 maxSize = 1;

    char bytes000B[1]; // Model Bit - 0x27 - HD 500 ; 0x28 - HD Desktop ; 0x29 - HD Pro
    char bytes000C[1]; // Major Version 0x01 == v1.x ; here set to v2.21
    char bytes000D[1]; // Minor Version 0x06 == vx.06 ;

    char bytes0013[1]; // don't know, whats good for. Changing in random value doesn't matter
    char bytes0014[1]; // default with blank preset: HD Pro 0x04 0x00 0x02
    char bytes0015[1]; // HD 500 0x02 0x01 0x30 ; HD Desktop 0x03 0x01 0x01

    if (pressedFrom.compare("Desktop") == 0) {
        bytes000B[0] = '\x28'; // Model Bit - 0x27 - HD 500 ; 0x28 - HD Desktop ; 0x29 - HD Pro
        bytes000C[0] = '\x02'; // Major Version 0x01 == v1.x ; here set to v2.21
        bytes000D[0] = '\x21'; // Minor Version 0x06 == vx.06 ;

        bytes0013[0] = '\x03'; // don't know, whats good for. Changing in random value doesn't matter
        bytes0014[0] = '\x01'; // default with blank preset: HD Pro 0x04 0x00 0x02
        bytes0015[0] = '\x01'; // HD 500 0x02 0x01 0x30 ; HD Desktop 0x03 0x01 0x01
    } else if (pressedFrom.compare("500") == 0) {
        bytes000B[0] = '\x27';
        bytes000C[0] = '\x02';
        bytes000D[0] = '\x21';
        bytes0013[0] = '\x02';
        bytes0014[0] = '\x01';
        bytes0015[0] = '\x30';
    } else if (pressedFrom.compare("Pro") == 0) {
        bytes000B[0] = '\x29';
        bytes000C[0] = '\x02';
        bytes000D[0] = '\x00';
        bytes0013[0] = '\x04';
        bytes0014[0] = '\x00';
        bytes0015[0] = '\x02';
    }

    //const char bytes0DFA[] = { '\x07' };
    //const char bytes1026[] = { '\x01' };
    //const char bytes1027[] = { '\x00' };

    for (int i = 0; i < presetFiles.count(); i++) {
        QFile fileToModify(presetFiles[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {
                fileToModify.seek(0x000B);
                fileToModify.write(bytes000B, maxSize);
                fileToModify.seek(0x000C);
                fileToModify.write(bytes000C, maxSize);
                fileToModify.seek(0x000D);
                fileToModify.write(bytes000D, maxSize);
                fileToModify.seek(0x0013);
                fileToModify.write(bytes0013, maxSize);
                fileToModify.seek(0x0014);
                fileToModify.write(bytes0014, maxSize);
                fileToModify.seek(0x0015);
                fileToModify.write(bytes0015, maxSize);
                //fileToModify.seek(0x0DFA);
                //fileToModify.write(guitarIn, maxSize);
                //fileToModify.seek(0x1026);
                //fileToModify.write(sourceOne, maxSize);
                //fileToModify.seek(0x1027);
                //fileToModify.write(sourceTwo, maxSize);
                fileToModify.close();
        }
    }
}

void MainWindow::convertBundleFiles(QStringList presetFiles, QString pressedFrom) {

    qint64 maxSize = 1;

    char bytes00000B[1]; // Unknown Triple Bytes - See Explaination above at convertPresetFiles.
    char bytes00000C[1];
    char bytes00000D[1];
    char bytes000017[1]; // Model number. See above at converPresetFiles.

    char bytes000033[1];
    char bytes000034[1];
    char bytes000035[1];
    char bytes00003F[1];

    char bytes00006B[1];
    char bytes000073[1];
    char bytes000074[1];
    char bytes000075[1];

    // Content 1-8

    char bytes001093[1];
    char bytes00109B[1];
    char bytes00109C[1];
    char bytes00109D[1];

    // Setlist 2-8

    char bytes040A5E[1]; // ?

    char bytes040A6B[1];
    char bytes040A6C[1];
    char bytes040A6D[1];
    char bytes040A77[1];
    char bytes040AA3[1];
    char bytes040AAB[1];
    char bytes040AAC[1];
    char bytes040AAD[1];

    if (pressedFrom.compare("Desktop") == 0) {

        // Header

        bytes00000B[0] = '\x03'; // Unknown Triple Bytes - See Explaination above at convertPresetFiles.
        bytes00000C[0] = '\x01';
        bytes00000D[0] = '\x01';
        bytes000017[0] = '\x28'; // Model number. See above at converPresetFiles.

        bytes000033[0] = '\x03';
        bytes000034[0] = '\x01';
        bytes000035[0] = '\x01';
        bytes00003F[0] = '\x28';

        bytes00006B[0] = '\x28';
        bytes000073[0] = '\x03';
        bytes000074[0] = '\x01';
        bytes000075[0] = '\x01';

        // Content 1-8

        bytes001093[0] = '\x28';
        bytes00109B[0] = '\x03';
        bytes00109C[0] = '\x03';
        bytes00109D[0] = '\x01';

        // Setlist 2-8

        bytes040A5E[0] = '\x01'; // ?

        bytes040A6B[0] = '\x03';
        bytes040A6C[0] = '\x01';
        bytes040A6D[0] = '\x01';
        bytes040A77[0] = '\x28';
        bytes040AA3[0] = '\x28';
        bytes040AAB[0] = '\x03';
        bytes040AAC[0] = '\x01';
        bytes040AAD[0] = '\x01';

    } else if (pressedFrom.compare("500") == 0) {

        // Header

        bytes00000B[0] = '\x02';
        bytes00000C[0] = '\x01';
        bytes00000D[0] = '\x30';
        bytes000017[0] = '\x27';

        bytes000033[0] = '\x02';
        bytes000034[0] = '\x01';
        bytes000035[0] = '\x30';
        bytes00003F[0] = '\x27';

        bytes00006B[0] = '\x27';
        bytes000073[0] = '\x02';
        bytes000074[0] = '\x01';
        bytes000075[0] = '\x30';

        // Content 1-8

        bytes001093[0] = '\x27';
        bytes00109B[0] = '\x02';
        bytes00109C[0] = '\x01';
        bytes00109D[0] = '\x30';

        // Setlist 2-8

        bytes040A5E[0] = '\x01'; // ?

        bytes040A6B[0] = '\x02';
        bytes040A6C[0] = '\x01';
        bytes040A6D[0] = '\x30';
        bytes040A77[0] = '\x27';
        bytes040AA3[0] = '\x27';
        bytes040AAB[0] = '\x02';
        bytes040AAC[0] = '\x01';
        bytes040AAD[0] = '\x30';

    } else if (pressedFrom.compare("Pro") == 0) {

        // Header

        bytes00000B[0] = '\x04';
        bytes00000C[0] = '\x00';
        bytes00000D[0] = '\x02';
        bytes000017[0] = '\x29';

        bytes000033[0] = '\x04';
        bytes000034[0] = '\x00';
        bytes000035[0] = '\x02';
        bytes00003F[0] = '\x29';

        bytes00006B[0] = '\x29';
        bytes000073[0] = '\x04';
        bytes000074[0] = '\x00';
        bytes000075[0] = '\x02';

        // Content 1-8

        bytes001093[0] = '\x29';
        bytes00109B[0] = '\x04';
        bytes00109C[0] = '\x00';
        bytes00109D[0] = '\x02';

        // Setlist 2-8

        bytes040A5E[0] = '\x01'; // ?

        bytes040A6B[0] = '\x04';
        bytes040A6C[0] = '\x00';
        bytes040A6D[0] = '\x02';
        bytes040A77[0] = '\x29';
        bytes040AA3[0] = '\x29';
        bytes040AAB[0] = '\x04';
        bytes040AAC[0] = '\x00';
        bytes040AAD[0] = '\x02';
    }

    //const char bytes000E5A[] = { '\x07' };

    // Content 1-8

    //const char bytes000E5A[] = { '\x07' };
    //const char bytes001086[] = { '\x01' };
    //const char bytes001087[] = { '\x00' };

    // Footer

    //const char bytes2051E6[] = "\x01";

    // Seek and Write

    for (int i = 0; i < presetFiles.count(); i++) {
        QFile fileToModify(presetFiles[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

                // Header
                fileToModify.seek(0x00000B);
                fileToModify.write(bytes00000B, maxSize);
                fileToModify.seek(0x00000C);
                fileToModify.write(bytes00000C, maxSize);
                fileToModify.seek(0x00000D);
                fileToModify.write(bytes00000D, maxSize);
                fileToModify.seek(0x000017);
                fileToModify.write(bytes000017, maxSize);
                fileToModify.seek(0x000033);
                fileToModify.write(bytes000033, maxSize);
                fileToModify.seek(0x000034);
                fileToModify.write(bytes000034, maxSize);
                fileToModify.seek(0x000035);
                fileToModify.write(bytes000035, maxSize);
                fileToModify.seek(0x00003F);
                fileToModify.write(bytes00003F, maxSize);
                fileToModify.seek(0x00006B);
                fileToModify.write(bytes00006B, maxSize);
                fileToModify.seek(0x000073);
                fileToModify.write(bytes000073, maxSize);
                fileToModify.seek(0x000074);
                fileToModify.write(bytes000074, maxSize);
                fileToModify.seek(0x000075);
                fileToModify.write(bytes000075, maxSize);
                //fileToModify.seek(0x000E5A);
                //fileToModify.write(bytes000E5A, maxSize);

                // Content
                for (int j=0; j<8; j++) {
                    for (int i=0; i<64; i++) {
                        //fileToModify.seek((0x000E5A + (j * 0x040A38)) + (i * 0x001028));
                        //fileToModify.write(guitarIn, maxSize);
                        //fileToModify.seek((0x001086 + (j * 0x040A38)) + (i * 0x001028));
                        //fileToModify.write(sourceOne, maxSize);
                        //fileToModify.seek((0x001087 + (j * 0x040A38)) + (i * 0x001028));
                        //fileToModify.write(sourceTwo, maxSize);
                        fileToModify.seek((0x001093 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(bytes001093, maxSize);
                        fileToModify.seek((0x00109B + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(bytes00109B, maxSize);
                        fileToModify.seek((0x00109C + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(bytes00109C, maxSize);
                        fileToModify.seek((0x00109D + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(bytes00109D, maxSize);
                    }
                }

                // Setlist
                for (int i=0; i<7; i++) {
                    fileToModify.seek(0x040A5E + (i * 0x040A38));
                    fileToModify.write(bytes040A5E, maxSize);
                    fileToModify.seek(0x040A6B + (i * 0x040A38));
                    fileToModify.write(bytes040A6B, maxSize);
                    fileToModify.seek(0x040A6C + (i * 0x040A38));
                    fileToModify.write(bytes040A6C, maxSize);
                    fileToModify.seek(0x040A6D + (i * 0x040A38));
                    fileToModify.write(bytes040A6D, maxSize);
                    fileToModify.seek(0x040A77 + (i * 0x040A38));
                    fileToModify.write(bytes040A77, maxSize);
                    fileToModify.seek(0x040AA3 + (i * 0x040A38));
                    fileToModify.write(bytes040AA3, maxSize);
                    fileToModify.seek(0x040AAB + (i * 0x040A38));
                    fileToModify.write(bytes040AAB, maxSize);
                    fileToModify.seek(0x040AAC + (i * 0x040A38));
                    fileToModify.write(bytes040AAC, maxSize);
                    fileToModify.seek(0x040AAD + (i * 0x040A38));
                    fileToModify.write(bytes040AAD, maxSize);
                }

                // Footer
                //fileToModify.seek(0x2051E6);
                //fileToModify.write(bytes2051E6, maxSize);

                // Close file
                fileToModify.close();
        }
    }
}


void MainWindow::convertSetlistFiles(QStringList presetFiles, QString pressedFrom) {

    qint64 maxSize = 1;

    char bytes00000B[1];
    char bytes00000C[1];
    char bytes00000D[1];
    char bytes000017[1];
    char bytes000043[1];
    char bytes00004B[1];
    char bytes00004C[1];
    char bytes00004D[1];

    // Content 1-8

    char bytes00106B[1];
    char bytes001073[1];
    char bytes001074[1];
    char bytes001075[1];


    if (pressedFrom.compare("Pro") == 0) {

        // Header

        bytes00000B[0] = '\x04';
        bytes00000C[0] = '\x00';
        bytes00000D[0] = '\x02';
        bytes000017[0] = '\x29';
        bytes000043[0] = '\x29';
        bytes00004B[0] = '\x04';
        bytes00004C[0] = '\x00';
        bytes00004D[0] = '\x02';

        // Content 1-8

        bytes00106B[0] = '\x29';
        bytes001073[0] = '\x04';
        bytes001074[0] = '\x00';
        bytes001075[0] = '\x02';

    } else if (pressedFrom.compare("500") == 0) {

        // Header

        bytes00000B[0] = '\x02';
        bytes00000C[0] = '\x01';
        bytes00000D[0] = '\x30';
        bytes000017[0] = '\x27';
        bytes000043[0] = '\x27';
        bytes00004B[0] = '\x02';
        bytes00004C[0] = '\x01';
        bytes00004D[0] = '\x30';

        // Content 1-8

        bytes00106B[0] = '\x27';
        bytes001073[0] = '\x02';
        bytes001074[0] = '\x01';
        bytes001075[0] = '\x30';

    } else if (pressedFrom.compare("Desktop") == 0) {

        // Header

        bytes00000B[0] = '\x03';
        bytes00000C[0] = '\x01';
        bytes00000D[0] = '\x01';
        bytes000017[0] = '\x28';
        bytes000043[0] = '\x28';
        bytes00004B[0] = '\x03';
        bytes00004C[0] = '\x01';
        bytes00004D[0] = '\x01';

        // Content 1-8

        bytes00106B[0] = '\x28';
        bytes001073[0] = '\x03';
        bytes001074[0] = '\x01';
        bytes001075[0] = '\x01';

    }

    // Header


    //const char bytes000E32[] = { '\x07' };

    // Content 1-8

    //const char bytes000E32[] = { '\x07' };
    //const char bytes00105E[] = { '\x01' };
    //const char bytes00105F[] = { '\x00' };

    // Footer

    //const char bytes040A36[] = { '\x01' };

    // Seek and Write

    for (int i = 0; i < presetFiles.count(); i++) {
        QFile fileToModify(presetFiles[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

                // Header
                fileToModify.seek(0x00000B);
                fileToModify.write(bytes00000B, maxSize);
                fileToModify.seek(0x00000C);
                fileToModify.write(bytes00000C, maxSize);
                fileToModify.seek(0x00000D);
                fileToModify.write(bytes00000D, maxSize);
                fileToModify.seek(0x000017);
                fileToModify.write(bytes000017, maxSize);
                fileToModify.seek(0x000043);
                fileToModify.write(bytes000043, maxSize);
                fileToModify.seek(0x00004B);
                fileToModify.write(bytes00004B, maxSize);
                fileToModify.seek(0x00004C);
                fileToModify.write(bytes00004C, maxSize);
                fileToModify.seek(0x00004D);
                fileToModify.write(bytes00004D, maxSize);
                //fileToModify.seek(0x000E32);
                //fileToModify.write(bytes000E32, maxSize);

                // Content
                for (int i=0; i<64; i++) {
                    //fileToModify.seek(0x000E32 + (i * 0x001028));
                    //fileToModify.write(guitarIn, maxSize);
                    //fileToModify.seek(0x00105E + (i * 0x001028));
                    //fileToModify.write(sourceOne, maxSize);
                    //fileToModify.seek(0x00105F + (i * 0x001028));
                    //fileToModify.write(sourceTwo, maxSize);
                    fileToModify.seek(0x00106B + (i * 0x001028));
                    fileToModify.write(bytes00106B, maxSize);
                    fileToModify.seek(0x001073 + (i * 0x001028));
                    fileToModify.write(bytes001073, maxSize);
                    fileToModify.seek(0x001074 + (i * 0x001028));
                    fileToModify.write(bytes001074, maxSize);
                    fileToModify.seek(0x001075 + (i * 0x001028));
                    fileToModify.write(bytes001075, maxSize);
                }

                // Footer
                //fileToModify.seek(0x040A36);
                //fileToModify.write(bytes040A36, maxSize);

                // Close file
                fileToModify.close();
        }
    }

}

void MainWindow::translatePresetFiles(QDir source, QStringList files, QStringList extension, const bool override) {

    bool error = false;

    // Generate basic Filestructure

    const char h3eStructure[] = {
        0x48,0x33,0x45,0x50,0x00,0x00,0x00,0x01,0x7D,0x01,0x00,0x25,0x02,0x01,0x00,0x00,0x00,
        0x14,0x00,0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x65,0x66,0x61,0x75,0x6C,0x74,0x20,0x50,0x72,0x65,
        0x73,0x65,0x74,0x20,0x20,0x00,0x80,0x00,0x00,0x00,0x00,0x40,0x00,0x40,0x00,0x40,0x00,
        0x40,0x00,0x40,0x00,0x40,0x00,0x1F,0x03,0x00,0x00,0x00,0x00,0x7F,0xFF,0x12,0x7B,0x00,
        0x00,0x7F,0xFF,0xE8,0x90,0x0E,0x2F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x0A,0x00,0x01,0x04,0x07,0x01,0x04,0x00,0x00,0x00,0x01,
        0x02,0x03,0x00,0x04,0x00,0x00,0x00,0x04,0x05,0x06,0x00,0x00,0x00,0x00,0x00,0x07,0x08,
        0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00};

    int lenH3eStructure = sizeof(h3eStructure)/sizeof(h3eStructure[0]);

    char hexIn[1], hexOut[1];

    bool ampOn = false, reverbPrePost = false, hasNoiseGate = false, hasWah = false;
    bool amp2On = false;

    bool hasDualamp = false;

    // Bytes to define FX status

    char fxOffPre[1] = { 0x00 };
    char fxOffPost[1] = { 0x02 };
    char fxOnPre[1] = { 0x04 };
    char fxOnPost[1] = { 0x06 };

    QHash<char,char> Amps;
    Amps.insert(0x05, 0x00);
    Amps.insert(0x06, 0x10);
    Amps.insert(0x08, 0x01);
    Amps.insert(0x0E, 0x02);
    Amps.insert(0x14, 0x03);
    Amps.insert(0x01, 0x04);
    Amps.insert(0x02, 0x11);
    Amps.insert(0x03, 0x05);
    Amps.insert(0x04, 0x12);
    Amps.insert(0x12, 0x06);
    Amps.insert(0x00, 0x07);
    Amps.insert(0x10, 0x08);
    Amps.insert(0x11, 0x09);
    Amps.insert(0x09, 0x13);
    Amps.insert(0x0A, 0x0A);
    Amps.insert(0x55, 0x16);
    Amps.insert(0x58, 0x17);
    Amps.insert(0x0C, 0x14);
    Amps.insert(0x0D, 0x0B);
    Amps.insert(0x15, 0x0C);
    Amps.insert(0x17, 0x0D);
    Amps.insert(0x0B, 0x0E);
    Amps.insert(0x19, 0x0F);
    Amps.insert(0x52, 0x15);
    Amps.insert(0x5E, 0x18);
    Amps.insert(0x61, 0x19);
    Amps.insert(0x64, 0x1A);
    Amps.insert(0x67, 0x1B);
    Amps.insert(0x6A, 0x1C);
    Amps.insert(0x5B, 0x1D);

    // Pre Models
    Amps.insert(0x20, 0x00);
    Amps.insert(0x21, 0x10);
    Amps.insert(0x23, 0x01);
    Amps.insert(0x29, 0x02);
    Amps.insert(0x2F, 0x03);
    Amps.insert(0x1C, 0x04);
    Amps.insert(0x1D, 0x11);
    Amps.insert(0x1E, 0x05);
    Amps.insert(0x1F, 0x12);
    Amps.insert(0x2D, 0x06);
    Amps.insert(0x1B, 0x07);
    Amps.insert(0x2B, 0x08);
    Amps.insert(0x2C, 0x09);
    Amps.insert(0x24, 0x13);
    Amps.insert(0x25, 0x0A);   
    Amps.insert(0x56, 0x16);
    Amps.insert(0x59, 0x17);
    Amps.insert(0x27, 0x14);
    Amps.insert(0x28, 0x0B);
    Amps.insert(0x30, 0x0C);
    Amps.insert(0x32, 0x0D);
    Amps.insert(0x26, 0x0E);
    Amps.insert(0x34, 0x0F);
    Amps.insert(0x53, 0x15);
    Amps.insert(0x5F, 0x18);
    Amps.insert(0x62, 0x19);
    Amps.insert(0x65, 0x1A);
    Amps.insert(0x68, 0x1B);
    Amps.insert(0x6B, 0x1C);
    Amps.insert(0x5C, 0x19);

    QHash<char,char> PreAmps;

    // Pre Models
    PreAmps.insert(0x20, 0x00);
    PreAmps.insert(0x21, 0x10);
    PreAmps.insert(0x23, 0x01);
    PreAmps.insert(0x29, 0x02);
    PreAmps.insert(0x2F, 0x03);
    PreAmps.insert(0x1C, 0x04);
    PreAmps.insert(0x1D, 0x11);
    PreAmps.insert(0x1E, 0x05);
    PreAmps.insert(0x1F, 0x12);
    PreAmps.insert(0x2D, 0x06);
    PreAmps.insert(0x1B, 0x07);
    PreAmps.insert(0x2B, 0x08);
    PreAmps.insert(0x2C, 0x09);
    PreAmps.insert(0x24, 0x13);
    PreAmps.insert(0x25, 0x0A);  
    PreAmps.insert(0x56, 0x16);
    PreAmps.insert(0x59, 0x17);
    PreAmps.insert(0x27, 0x14);
    PreAmps.insert(0x28, 0x0B);
    PreAmps.insert(0x30, 0x0C);
    PreAmps.insert(0x32, 0x0D);
    PreAmps.insert(0x26, 0x0E);
    PreAmps.insert(0x34, 0x0F);
    PreAmps.insert(0x53, 0x15);
    PreAmps.insert(0x5F, 0x18);
    PreAmps.insert(0x62, 0x19);
    PreAmps.insert(0x65, 0x1A);
    PreAmps.insert(0x68, 0x1B);
    PreAmps.insert(0x6B, 0x1C);
    PreAmps.insert(0x5C, 0x19);

    QHash<char,char> Cabs;
    Cabs.insert(0x00, 0x08);
    Cabs.insert(0x01, 0x03);
    Cabs.insert(0x02, 0x07);
    Cabs.insert(0x03, 0x06);
    Cabs.insert(0x04, 0x04);
    Cabs.insert(0x05, 0x09);
    Cabs.insert(0x06, 0x01);
    Cabs.insert(0x08, 0x0A);
    Cabs.insert(0x09, 0x05);
    Cabs.insert(0x0A, 0x0E);
    Cabs.insert(0x0B, 0x10);
    Cabs.insert(0x0C, 0x02);
    Cabs.insert(0x0E, 0x0B);
    Cabs.insert(0x11, 0x0C);
    Cabs.insert(0x10, 0x0F);
    Cabs.insert(0x0F, 0x0D);
    Cabs.insert(0x12, 0x11);

    // Effects

    // Dynamics
    QHash<int,int> Dyn1;
    Dyn1.insert(0x12, 0x12);
    Dyn1.insert(0x0B, 0x13);
    Dyn1.insert(0x0C, 0x14);
    Dyn1.insert(0x0F, 0x16);
    Dyn1.insert(0x13, 0x5F);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        Dyn1.insert(0x0D, 0x15); // Blue Comp Treb -> Blue Comp
        Dyn1.insert(0x10, 0x17); // Vetta Juice -> Vetta Comp
    } else {
        Dyn1.insert(0x0D, 0x14); // Blue Comp Treb -> Blue Comp
        Dyn1.insert(0x10, 0x16); // Vetta Juice -> Vetta Comp
    }
    Dyn1.insert(0x0E, 0x13); // Tube Comp -> Red Comp


    // Distortion
    QHash<int,int> Dist1;
    Dist1.insert(0x0E, 0x01);
    Dist1.insert(0x0D, 0x0B);
    Dist1.insert(0x0B, 0x0C);
    Dist1.insert(0x16, 0x0D);
    Dist1.insert(0x18, 0x0E);
    Dist1.insert(0x10, 0x0F);
    Dist1.insert(0x13, 0x10);
    Dist1.insert(0x12, 0x11);
    Dist1.insert(0x0F, 0x18);
    Dist1.insert(0x0C, 0x19);
    Dist1.insert(0x0A, 0x1A);
    Dist1.insert(0x14, 0x1B);
    Dist1.insert(0x11, 0x1D);
    Dist1.insert(0x17, 0x1E);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        Dist1.insert(0x15, 0x1C); // Buzz Saw -> Jet Fuzz
    } else {
        Dist1.insert(0x15, 0x1A); // Buzz Saw -> Jet Fuzz
    }

    // Modulator
    QHash<int,int> Mod1;
    Mod1.insert(0x2E, 0x2A);
    Mod1.insert(0x2B, 0x2B);
    Mod1.insert(0x42, 0x2C);
    Mod1.insert(0x26, 0x2D);

    // Effect mapped (not available on hd300
    if (ui->threeChkbxPatchH4e->isChecked()) {
        Mod1.insert(0x27, 0x2E); // Rotary Dum & Horn -> Rotary Dum
    } else {
        Mod1.insert(0x27, 0x2D); // Rotary Dum & Horn -> Rotary Dum
    }

    QHash<int,int> Mod2;
    Mod2.insert(0x2A, 0x04);
    Mod2.insert(0x28, 0x36);
    Mod2.insert(0x25, 0x37);
    Mod2.insert(0x22, 0x38);
    Mod2.insert(0x23, 0x39);
    Mod2.insert(0x40, 0x3A);
    Mod2.insert(0x24, 0x3B);
    Mod2.insert(0x45, 0x3C);
    Mod2.insert(0x2D, 0x3D);
    Mod2.insert(0x20, 0x06);
    Mod2.insert(0x21, 0x42);
    Mod2.insert(0x43, 0x43);
    Mod2.insert(0x2F, 0x44);

    // Effect mapped (not available on hd300)

    Mod2.insert(0x2C, 0x04); // Tri Chorus -> Analog Chorus
    Mod2.insert(0x29, 0x36); // Jet Flanger -> Analog Flanger
    Mod2.insert(0x47, 0x36); // AC Flanger -> Analog Flanger
    Mod2.insert(0x49, 0x36); // 80A Flanger -> Analog Flanger

    // Filter
    QHash<int,int> Filter1;
    Filter1.insert(0x10, 0x27);
    Filter1.insert(0x0F, 0x28);
    Filter1.insert(0x14, 0x29);
    Filter1.insert(0x1C, 0x31);
    Filter1.insert(0x19, 0x32);
    Filter1.insert(0x1A, 0x33);
    Filter1.insert(0x1E, 0x35);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        Filter1.insert(0x1B, 0x30); // Attack Synth -> Synth String
    } else {
        Filter1.insert(0x1B, 0x31); // Attack Synth -> Synth String
    }

    QHash<int,int> Filter2;
    Filter2.insert(0x11, 0x05);
    Filter2.insert(0x15, 0x3E);
    Filter2.insert(0x16, 0x3F);
    Filter2.insert(0x14, 0x40);
    Filter2.insert(0x1D, 0x41);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        Filter2.insert(0x13, 0x26); // Slow Filter -> Throbber
        Filter2.insert(0x18, 0x5D); // Octisynth -> Spin Cycle
    } else {
        Filter2.insert(0x13, 0x3E); // Slow Filter -> Throbber
        Filter2.insert(0x18, 0x3F); // Octisynth -> Spin Cycle
    }
    Filter2.insert(0x26, 0x05); // Vocodoer -> Seeker
    Filter2.insert(0x17, 0x3F); // Comet Trails -> Spin Cycle

    // Pitcher
    QHash<int,int> Pitch1;
    Pitch1.insert(0x03, 0x03);
    Pitch1.insert(0x02, 0x2F);
    Pitch1.insert(0x04, 0x34);

    // Equalizer + Pre
    QHash<int,int> Eq1;
    Eq1.insert(0x0B, 0x23);
    Eq1.insert(0x0C, 0x24);
    Eq1.insert(0x0E, 0x5E);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        Eq1.insert(0x09, 0x21); // Graphic EQ -> Parametic EQ
        Eq1.insert(0x0A, 0x22); // Studio EQ -> 4 Band Shift EQ
        Eq1.insert(0x0D, 0x25); // Mid Focus EQ -> 4 Band Shift EQ
    } else {
        Eq1.insert(0x09, 0x23); // Graphic EQ -> Parametic EQ
        Eq1.insert(0x0A, 0x24); // Studio EQ -> 4 Band Shift EQ
        Eq1.insert(0x0D, 0x24); // Mid Focus EQ -> 4 Band Shift EQ
    }

    // Delay
    QHash<int,int> Delay3;
    Delay3.insert(0x11, 0x07);
    Delay3.insert(0x12, 0x45);
    Delay3.insert(0x14, 0x46);
    Delay3.insert(0x15, 0x47);
    Delay3.insert(0x30, 0x48);
    Delay3.insert(0x31, 0x49);
    Delay3.insert(0x1D, 0x4A);
    Delay3.insert(0x13, 0x4B);

    Delay3.insert(0x20, 0x4C);
    Delay3.insert(0x22, 0x4D);
    Delay3.insert(0x2C, 0x08);
    Delay3.insert(0x2D, 0x4E);
    Delay3.insert(0x2A, 0x4F);
    Delay3.insert(0x2B, 0x50);
    Delay3.insert(0x23, 0x09);
    Delay3.insert(0x2E, 0x52);
    Delay3.insert(0x2F, 0x53);
    Delay3.insert(0x21, 0x54);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        Delay3.insert(0x1A, 0x51); // Multi-Head Delay -> Digital Delay!?
    } else {
        Delay3.insert(0x1A, 0x07); // Multi-Head Delay -> Digital Delay!?
    }

    // Reverb
    QHash<int,int> Reverb1;
    Reverb1.insert(0x1D, 0x02);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        Reverb1.insert(0x1C, 0x1F); // '63 Spring -> Spring
        Reverb1.insert(0x27, 0x20); // Particle Verb -> Spring
    } else {
        Reverb1.insert(0x1C, 0x02); // '63 Spring -> Spring
        Reverb1.insert(0x27, 0x02); // Particle Verb -> Spring
    }

    QHash<int,int> ReverbSlot;
    ReverbSlot.insert(0x1E, 0x0A);
    ReverbSlot.insert(0x1F, 0x55);
    ReverbSlot.insert(0x20, 0x56);
    ReverbSlot.insert(0x21, 0x57);
    ReverbSlot.insert(0x24, 0x58);
    ReverbSlot.insert(0x23, 0x5A);
    ReverbSlot.insert(0x25, 0x5B);
    ReverbSlot.insert(0x26, 0x5C);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        ReverbSlot.insert(0x22, 0x59); // Ducking -> Cave
    } else {
        ReverbSlot.insert(0x22, 0x58); // Ducking -> Cave
    }

    // Wah
    QHash<int,int> WahSlot;
    WahSlot.insert(0x0B, 0x00);
    WahSlot.insert(0x0C, 0x01);
    WahSlot.insert(0x0E, 0x02);
    WahSlot.insert(0x0D, 0x03);
    WahSlot.insert(0x11, 0x04);
    WahSlot.insert(0x12, 0x05);

    // Effect mapped (not available on hd300)
    if (ui->threeChkbxPatchH4e->isChecked()) {
        WahSlot.insert(0x10, 0x06); // Throaty -> Conductor
        WahSlot.insert(0x0F, 0x07); // Chrome Custom -> Chrome
    } else {
        WahSlot.insert(0x10, 0x04); // Throaty -> Conductor
        WahSlot.insert(0x0F, 0x02); // Chrome Custom -> Chrome
    }


    // Create Translated Preset

    QList<QString>::iterator f;

    for (f = files.begin(); f != files.end(); ++f) {

        QFileInfo sourceFileInfo((*f));
        QString targetFileName = source.path() + QDir::separator() + sourceFileInfo.baseName() + extension[0];

        QFile sourceFile((*f));
        QFile targetFile(targetFileName);

        if (targetFile.exists() && override) {
            targetFile.remove();
        }

        // Open SourceFile

        sourceFile.open(QIODevice::ReadOnly);

        // Create and open TargetFile

        if (!targetFile.open( QIODevice::ReadWrite )) {
#ifdef QT_DEBUG
            std::cout << "createFile err: "<< (sourceFileInfo.baseName() + extension[0]).toStdString() << std::endl;
#endif
            error = true;
        }

        // Start Writing
        // Write default template

        targetFile.write(h3eStructure,lenH3eStructure);

        // Set Preset Name

        char presetName[16];
        sourceFile.seek(0x28);
        sourceFile.read(presetName,16);
        targetFile.seek(0x28);
        targetFile.write(presetName, 16);

        // Check if Amp is On
        sourceFile.seek(0x58);
        sourceFile.read(hexIn,1);
        if(hexIn[0] == 0x01) {
            ampOn = true;
        }

        // Seek and Write for first Amp Model

        sourceFile.seek(0x53);
        sourceFile.read(hexIn, 1);
        targetFile.seek(0x3B);
        hexOut[0] = Amps.value(hexIn[0]);
        targetFile.write(hexOut, 1);

        // Check for PreAmp
        sourceFile.seek(0x53);
        char checkPreamp[1];
        sourceFile.read(checkPreamp, 1);
        if(PreAmps.contains(checkPreamp[0])) {
            targetFile.seek(0x4D);
            targetFile.write("\x01", 1);
        } else {
            targetFile.seek(0x4D);
            targetFile.write("\x00", 1);
        }

        // Turn first Cab On

        sourceFile.seek(0x25B);
        sourceFile.read(hexIn, 1);
        if(hexIn == 0x00) {
            targetFile.seek(0x3D);
            targetFile.write("\x12", 1);
        }

        // Seek and Write for first Cab Model

        sourceFile.seek(0x253);
        sourceFile.read(hexIn, 1);
        targetFile.seek(0x3D);
        hexOut[0] = Cabs.value(hexIn[0]);
        targetFile.write(hexOut, 1);

        // Convert (From 4 Bytes (float) to 2 Bytes (int)) Amp Potis and write them down
        // Drive
        poti(sourceFile, targetFile, 0x64, 0x3E);

        // Bass
        poti(sourceFile, targetFile, 0x78, 0x40);

        // Mid
        poti(sourceFile, targetFile, 0x8C, 0x42);

        // Treble
        poti(sourceFile, targetFile, 0xA0, 0x44);

        // Pres
        poti(sourceFile, targetFile, 0xB4, 0x48);

        // CH. Vol
        poti(sourceFile, targetFile, 0xC8, 0x46);

        // E.R.
        poti(sourceFile, targetFile, 0xD74, 0x4E);



        // BYP Vol.
        poti(sourceFile, targetFile, 0xDA4, 0x50);



        // Master
        poti(sourceFile, targetFile, 0x12C, 0x64);

        // Sag
        poti(sourceFile, targetFile, 0xF0, 0x5E);

        // Hum
        poti(sourceFile, targetFile, 0xDC, 0x5C);

        // Bias
        poti(sourceFile, targetFile, 0x104, 0x60);

        // Bias X
        poti(sourceFile, targetFile, 0x118, 0x62);

        // Cab Parameter (Not Available on POD HD 300?)

        // Low Cut
        //poti(sourceFile, targetFile, 0x264, 0x);

        // Res Level
        //poti(sourceFile, targetFile, 0x278, 0x);

        // Thump
        //poti(sourceFile, targetFile, 0x28C, 0x);

        // Decay
        //poti(sourceFile, targetFile, 0x2A0, 0x);

        // Microphone

        sourceFile.seek(0x1020);
        sourceFile.read(hexIn, 1);
        targetFile.seek(0x4C);
        targetFile.write(hexIn, 1);

        // Effects

        // Check which effects are available

        char effectType[1], effectModell[1];

        // holds Number of Effects in Slots (HD 300)
        int fx1 = 0, fx2 = 0, fx3 = 0, reverbSlot = 0, Wah = 0;

        // Check for Number of Effects in Slots

        for (int j = 0x0; j<0x800; j += 0x100) {

            sourceFile.seek(0x451 + j);
            sourceFile.read(effectType, 1);

            switch (effectType[0]) {
            case 0x00:
                // Dyn Effect

                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);

                // Check for Noise Gate

                // Set Effect
                if (Dyn1.contains(effectModell[0])) {

                    fx1 += 1;
                }
                break;
            case 0x05:
                // Dist Effect

                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);
                if (Dist1.contains(effectModell[0])) {

                    fx1 += 1;
                }
                break;
            case 0x03:
                // Mod Effect


                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);
                if (Mod1.contains(effectModell[0])) {

                    fx1 += 1;

                // Check for 2nd Slot

                // Check for Type of Effect
                } else if (Mod2.contains(effectModell[0])) {

                    fx2 += 1;
                }
                break;
            case 0x0A:
                // Filter Effect

                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);
                if (Filter1.contains(effectModell[0])) {

                    fx1 += 1;

                // Check for 2nd Slot

                // Check for Type of Effect
                } else if (Filter2.contains(effectModell[0])) {

                    fx2 += 1;
                }
                break;
            case 0x09:
                // Pitch Effect

                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);
                if (Pitch1.contains(effectModell[0])) {


                    fx1 += 1;
                }
                break;
            case 0x0C:
                //  EQ+Pre Effect

                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);
                if (Eq1.contains(effectModell[0])) {

                    fx1 += 1;
                }
                break;
            case 0x02:
                // Delay Effect

                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);
                if (Delay3.contains(effectModell[0])) {

                    fx3 += 1;
                }
                break;
            case 0x04:
                // Reverb Effect

                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);
                if (Reverb1.contains(effectModell[0])) {

                    fx1 += 1;

                // Check for ReverbSlot

                // Check for Type of Effect
                } else if (ReverbSlot.contains(effectModell[0])) {

                    reverbSlot += 1;
                }
                break;
            case 0x07:
                //  VolPan Effect
                break;
            case 0x06:
                // Wah Effect

                // Check for Type of Effect
                sourceFile.seek(0x453 + j);
                sourceFile.read(effectModell, 1);
                if (WahSlot.contains(effectModell[0])) {

                    Wah += 1;
                }
                break;
            case 0x08:
                // FXLoop Effect
                break;
            }
        }

        targetFile.close();

        // Fix for Generating presets with unmodified, but available Effecs

        int v2 = 0, w2 = 0, x2 = 0, y2 = 0, z2 = 0;

        if (fx1 != 0) v2++;
        if (fx2 != 0) w2++;
        if (fx3 != 0) x2++;
        if (reverbSlot != 0) y2++;
        if (Wah != 0) z2++;

        for (int v=v2; v<=fx1; v++) {
            for (int w=w2; w<=fx2; w++) {
                for (int x=x2; x<=fx3; x++) {
                    for (int y=y2; y<=reverbSlot; y++) {
                        for (int z=z2; z<=Wah; z++) {

                            // Define FileNames

                            QFileInfo targetFileInfo(targetFile);
                            QString targetFileLoopName = source.path() + QDir::separator() + targetFileInfo.baseName() +
                                    QString::number(v) + QString::number(w) + QString::number(x) +
                                    QString::number(y) + QString::number(z) + "." + targetFileInfo.suffix();

                            // Copy Template to files

                            if (!targetFile.copy(targetFileLoopName)) {
#ifdef QT_DEBUG
                                    std::cout << "copyFile err: "<< targetFileName.toStdString() + "to" + targetFileLoopName.toStdString() << std::endl;
#endif
                                    error = true;
                                }

                            QFile targetFileLoop(targetFileLoopName);
                            if (!targetFileLoop.open( QIODevice::ReadWrite )) {
#ifdef QT_DEBUG
                                std::cout << "createFile err: "<< (targetFileInfo.baseName() + "." +targetFileInfo.suffix()).toStdString() << std::endl;
#endif
                                error = true;
                            }

                            int fx1a = 1, fx2a = 1, fx3a = 1, reverbSlota = 1, Waha = 1;

                            const QList<int> preEffects = QList<int>() << 0x00 << 0x01 << 0x02;
                            const QList<int> postEffects = QList<int>() << 0x03 << 0x04 << 0x05;

                            char effectOn[1], effectPrePost[1];

                            for (int j = 0x0; j<0x800; j += 0x100) {

                                sourceFile.seek(0x451 + j);
                                sourceFile.read(effectType, 1);

                                switch (effectType[0]) {
                                case 0x00:
                                    // Dyn Effect

                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);

                                    // Check for Noise Gate

                                    if (effectModell[0] == 0x11) {
                                        // Found NoiseGate

                                        // 1. Poti -- Tresh
                                        potiDecibel(sourceFile, targetFileLoop, 0x464 + j, 0x58);

                                        // 2. Poti -- Decay
                                        poti(sourceFile, targetFileLoop, 0x478 + j, 0x5A);

                                        hasNoiseGate = true;
                                    }

                                    // Set Effect
                                    if (Dyn1.contains(effectModell[0])) {
                                        if (fx1a == v) {
                                            targetFileLoop.seek(0x75);
                                            hexOut[0] = Dyn1.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x75);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6E);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x8C);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x8E);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x90);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x92);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0x94);

                                        }
                                        fx1a += 1;

                                    }
                                    break;
                                case 0x05:
                                    // Dist Effect

                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);
                                    if (Dist1.contains(effectModell[0])) {
                                        if (fx1a == v) {

                                            targetFileLoop.seek(0x75);
                                            hexOut[0] = Dist1.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x75);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6E);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x8C);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x8E);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x90);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x92);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0x94);

                                        }
                                        fx1a++;

                                    }
                                    break;
                                case 0x03:
                                    // Mod Effect


                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);
                                    if (Mod1.contains(effectModell[0])) {
                                        if (fx1a == v) {

                                            targetFileLoop.seek(0x75);
                                            hexOut[0] = Mod1.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x75);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6E);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x8C);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x8E);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x90);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x92);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0x94);

                                        }
                                        fx1a += 1;

                                    // Check for 2nd Slot


                                    // Check for Type of Effect
                                    } else if (Mod2.contains(effectModell[0])) {
                                        if (fx2a == w) {

                                            targetFileLoop.seek(0x7D);
                                            hexOut[0] = Mod2.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x7D);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6F);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x7A);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x7A);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x7A);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x7A);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x96);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x98);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x9A);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x9C);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0xA0);

                                        }
                                        fx2a += 1;

                                    }
                                    break;
                                case 0x0A:
                                    // Filter Effect

                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);
                                    if (Filter1.contains(effectModell[0])) {
                                        if (fx1a == v) {

                                            targetFileLoop.seek(0x75);
                                            hexOut[0] = Filter1.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x75);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6E);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x8C);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x8E);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x90);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x92);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0x94);

                                        }
                                        fx1a += 1;

                                    // Check for 2nd Slot

                                    // Check for Type of Effect
                                    } else if (Filter2.contains(effectModell[0])) {
                                        if (fx2a == w) {
                                            targetFileLoop.seek(0x7D);
                                            hexOut[0] = Filter2.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x7D);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6F);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x7A);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x7A);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x7A);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x7A);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x96);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x98);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x9A);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x9C);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0xA0);

                                        }
                                        fx2a += 1;

                                    }
                                    break;
                                case 0x09:
                                    // Pitch Effect

                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);
                                    if (Pitch1.contains(effectModell[0])) {
                                        if (fx1a == v) {
                                            targetFileLoop.seek(0x75);
                                            hexOut[0] = Pitch1.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x75);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6E);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x8C);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x8E);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x90);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x92);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0x94);

                                        }
                                        fx1a += 1;

                                    }
                                    break;
                                case 0x0C:
                                    //  EQ+Pre Effect

                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);
                                    if (Eq1.contains(effectModell[0])) {
                                        if (fx1a == v) {
                                            targetFileLoop.seek(0x75);
                                            hexOut[0] = Eq1.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x75);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6E);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x8C);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x8E);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x90);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x92);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0x94);

                                        }
                                        fx1a += 1;

                                    }
                                    break;
                                case 0x02:
                                    // Delay Effect

                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);
                                    if (Delay3.contains(effectModell[0])) {
                                        if (fx3a == x) {
                                            targetFileLoop.seek(0x85);
                                            hexOut[0] = Delay3.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x85);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x70);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x82);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x82);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x82);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x82);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0xA2);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0xA4);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0xA6);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0xA8);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0xAA);

                                        }
                                        fx3a += 1;

                                    }
                                    break;
                                case 0x04:
                                    // Reverb Effect

                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);
                                    if (Reverb1.contains(effectModell[0])) {
                                        if (fx1a == v) {

                                            targetFileLoop.seek(0x75);
                                            hexOut[0] = Reverb1.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Write again at different Place
                                            targetFileLoop.seek(0x75);
                                            targetFileLoop.read(hexIn, 1);
                                            targetFileLoop.seek(0x6E);
                                            targetFileLoop.write(hexIn, 1);

                                            // See if Effect is Online and Set it On
                                            sourceFile.seek(0x45B + j);
                                            sourceFile.read(effectOn, 1);
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (effectOn[0] == 0x01 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPre, 1);
                                            } else if (effectOn[0] == 0x01 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOnPost, 1);
                                            } else if (effectOn[0] == 0x00 && preEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPre, 1);
                                            } else if (effectOn[0] == 0x00 && postEffects.contains(effectPrePost[0])) {
                                                targetFileLoop.seek(0x72);
                                                targetFileLoop.write(fxOffPost, 1);
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0x8C);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0x8E);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0x90);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0x92);

                                            // 5. Poti
                                            poti(sourceFile, targetFileLoop, 0x4B4 + j, 0x94);

                                        }
                                        fx1a += 1;

                                    // Check for ReverbSlot

                                    // Check for Type of Effect
                                    } else if (ReverbSlot.contains(effectModell[0])) {
                                        if (reverbSlota == y) {
                                            targetFileLoop.seek(0x6C);
                                            hexOut[0] = ReverbSlot.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Set Pre/Post since it is always on
                                            sourceFile.seek(0x455 + j);
                                            sourceFile.read(effectPrePost, 1);
                                            if (preEffects.contains(effectPrePost[0])) {
                                                reverbPrePost = false; // Set false if Pre
                                            } else if (postEffects.contains(effectPrePost[0])) {
                                                reverbPrePost = true; // Set true if Post
                                            }

                                            // Set Potis

                                            // 1. Poti
                                            poti(sourceFile, targetFileLoop, 0x464 + j, 0xB0);

                                            // 2. Poti
                                            poti(sourceFile, targetFileLoop, 0x478 + j, 0xB2);

                                            // 3. Poti
                                            poti(sourceFile, targetFileLoop, 0x48C + j, 0xB4);

                                            // 4. Poti
                                            poti(sourceFile, targetFileLoop, 0x4A0 + j, 0xB8);

                                        }
                                        reverbSlota += 1;

                                    }
                                    break;
                                case 0x07:
                                    //  VolPan Effect
                                    break;
                                case 0x06:
                                    // Wah Effect

                                    // Check for Type of Effect
                                    sourceFile.seek(0x453 + j);
                                    sourceFile.read(effectModell, 1);
                                    if (WahSlot.contains(effectModell[0])) {
                                        if (Waha == z) {
                                            targetFileLoop.seek(0x6D);
                                            hexOut[0] = WahSlot.value(effectModell[0]);
                                            targetFileLoop.write(hexOut, 1);

                                            // Set Potis

                                            // 1. Poti
                                            potiByte(sourceFile, targetFileLoop, 0x464 + j, 0xBA);

                                            hasWah = true;

                                        }
                                        Waha += 1;

                                    }
                                    break;
                                case 0x08:
                                    // FXLoop Effect
                                    break;
                                }
                            }

                            // Setup Amp, NoiseGate, Wah and Reverb Byte:

                            targetFileLoop.seek(0x39);
                            if (ampOn && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
                                targetFileLoop.write("\x80", 1);
                            } else if (ampOn && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
                                targetFileLoop.write("\x88", 1);
                            } else if (ampOn && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
                                targetFileLoop.write("\x81", 1);
                            } else if (ampOn && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
                                targetFileLoop.write("\x89", 1);
                            } else if (ampOn && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
                                targetFileLoop.write("\xC0", 1);
                            } else if (ampOn && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
                                targetFileLoop.write("\xC8", 1);
                            } else if (ampOn && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
                                targetFileLoop.write("\xC1", 1);
                            } else if (ampOn && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
                                targetFileLoop.write("\xC9", 1);

                            } else if (ampOn == false && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
                                targetFileLoop.write("\x00", 1);
                            } else if (ampOn == false && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
                                targetFileLoop.write("\x08", 1);
                            } else if (ampOn == false && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
                                targetFileLoop.write("\x01", 1);
                            } else if (ampOn == false && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
                                targetFileLoop.write("\x09", 1);
                            } else if (ampOn == false && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
                                targetFileLoop.write("\x40", 1);
                            } else if (ampOn == false && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
                                targetFileLoop.write("\x48", 1);
                            } else if (ampOn == false && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
                                targetFileLoop.write("\x41", 1);
                            } else if (ampOn == false && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
                                targetFileLoop.write("\x49", 1);
                            }

                            targetFileLoop.close();

                            // Check for Dualamp Preset and MultiSlot Assignment

                            // Check if 2nd Amp set (either off or on, but defined)
                            sourceFile.seek(0x15B);
                            sourceFile.read(hexIn, 1);
                            if(hexIn[0] == 0x01) {

                                // Found 2nd Amp, do something!
                                hasDualamp = true;

                            }

                            if (hasDualamp) {

                                char checkPreamp2[1];

                                //qDebug() << "dualamp!";

                                // Define Filename for 2nd Amp

                                QFileInfo targetFileLoopInfo(targetFileLoop);
                                QString targetFileLoopName2ndAmp = source.path() + QDir::separator() + targetFileLoopInfo.baseName() +
                                        "2ndAmp." + targetFileLoopInfo.suffix();

                                // Copy Template to files

                                if (!targetFileLoop.copy(targetFileLoopName2ndAmp)) {
#ifdef QT_DEBUG
                                        std::cout << "copyFile err: "<< targetFileLoopName.toStdString() + "to" + targetFileLoopName2ndAmp.toStdString() << std::endl;
#endif
                                        error = true;
                                    }

                                QFile targetFileLoop2ndAmp(targetFileLoopName2ndAmp);
                                if (!targetFileLoop2ndAmp.open( QIODevice::ReadWrite )) {
#ifdef QT_DEBUG
                                    std::cout << "openFile err: "<< (targetFileLoopInfo.baseName() + "2ndAmp" + targetFileLoopInfo.suffix()).toStdString() << std::endl;
#endif
                                    error = true;
                                }

                                // Check if second Amp is On
                                sourceFile.seek(0x158);
                                sourceFile.read(hexIn, 1);
                                if(hexIn[0] == 0x01) {
                                    amp2On = true;
                                }

                                // Turn second Amp On

                                // sourceFile.seek(0x58);
                                // sourceFile.read(hexIn, 1);
                                // targetFileLoop2ndAmp.seek(0x39);
                                // if(hexIn == 0x01) {
                                // 	targetFileLoop.write("\x80", 1);
                                // } else if (hexIn == 0x00) {
                                // 	targetFileLoop.write("\x00", 1);
                                // }

                                // Seek and Write for second Amp Model

                                sourceFile.seek(0x153);
                                sourceFile.read(hexIn, 1);
                                targetFileLoop2ndAmp.seek(0x3B);
                                hexOut[0] = Amps.value(hexIn[0]);
                                targetFileLoop2ndAmp.write(hexOut, 1);

                                // Check for PreAmp
                                sourceFile.seek(0x153);
                                sourceFile.read(checkPreamp2, 1);
                                if(PreAmps.contains(checkPreamp2[0])) {
                                    targetFileLoop2ndAmp.seek(0x4D);
                                    targetFileLoop2ndAmp.write("\x01", 1);
                                } else {
                                    targetFileLoop2ndAmp.seek(0x4D);
                                    targetFileLoop2ndAmp.write("\x00", 1);
                                }

                                // Turn second Cab On

                                sourceFile.seek(0x35B);
                                sourceFile.read(hexIn, 1);
                                if(hexIn[0] == 0x00) {
                                    targetFileLoop2ndAmp.seek(0x3D);
                                    targetFileLoop2ndAmp.write("\x12", 1);
                                }

                                // Seek and Write for second Cab Model

                                sourceFile.seek(0x353);
                                sourceFile.read(hexIn, 1);
                                targetFileLoop2ndAmp.seek(0x3D);
                                hexOut[0] = Cabs.value(hexIn[0]);
                                targetFileLoop2ndAmp.write(hexOut, 1);

                                // Convert (From 2 Bytes to 3 Bytes accuracy) Amp Potis and write them down
                                // Drive
                                poti(sourceFile, targetFileLoop2ndAmp, 0x164, 0x3E);

                                // Bass
                                poti(sourceFile, targetFileLoop2ndAmp, 0x178, 0x40);

                                // Mid
                                poti(sourceFile, targetFileLoop2ndAmp, 0x18C, 0x42);

                                // Treble
                                poti(sourceFile, targetFileLoop2ndAmp, 0x1A0, 0x44);

                                // Pres
                                poti(sourceFile, targetFileLoop2ndAmp, 0x1B4, 0x48);

                                // CH. Vol
                                poti(sourceFile, targetFileLoop2ndAmp, 0x1C8, 0x46);

                                // E.R.
                                poti(sourceFile, targetFileLoop2ndAmp, 0xD7C, 0x4E);



                                // BYP Vol.
                                poti(sourceFile, targetFileLoop2ndAmp, 0xDA8, 0x50);



                                // Master
                                poti(sourceFile, targetFileLoop2ndAmp, 0x22C, 0x64);

                                // Sag
                                poti(sourceFile, targetFileLoop2ndAmp, 0x2F0, 0x5E);

                                // Hum
                                poti(sourceFile, targetFileLoop2ndAmp, 0x2DC, 0x5C);

                                // Bias
                                poti(sourceFile, targetFileLoop2ndAmp, 0x204, 0x60);

                                // Bias X
                                poti(sourceFile, targetFileLoop2ndAmp, 0x218, 0x62);

                                // Cab Parameter (Not Available on POD HD 300?)

                                // Low Cut
                                //poti(sourceFile, targetFileLoop2ndAmp, 0x364, 0x);

                                // Res Level
                                //poti(sourceFile, targetFileLoop2ndAmp, 0x378, 0x);

                                // Thump
                                //poti(sourceFile, targetFileLoop2ndAmp, 0x38C, 0x);

                                // Decay
                                //poti(sourceFile, targetFileLoop2ndAmp, 0x3A0, 0x);

                                // Second Microphone

                                sourceFile.seek(0x1021);
                                sourceFile.read(hexIn, 1);
                                targetFileLoop2ndAmp.seek(0x4C);
                                targetFileLoop2ndAmp.write(hexIn ,1);

                                targetFileLoop2ndAmp.seek(0x39);
                                if (amp2On && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
                                    targetFileLoop2ndAmp.write("\x80", 1);
                                } else if (amp2On && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
                                    targetFileLoop2ndAmp.write("\x88", 1);
                                } else if (amp2On && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
                                    targetFileLoop2ndAmp.write("\x81", 1);
                                } else if (amp2On && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
                                    targetFileLoop2ndAmp.write("\x89", 1);
                                } else if (amp2On && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
                                    targetFileLoop2ndAmp.write("\xC0", 1);
                                } else if (amp2On && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
                                    targetFileLoop2ndAmp.write("\xC8", 1);
                                } else if (amp2On && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
                                    targetFileLoop2ndAmp.write("\xC1", 1);
                                } else if (amp2On && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
                                    targetFileLoop2ndAmp.write("\xC9", 1);

                                } else if (amp2On == false && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
                                    targetFileLoop2ndAmp.write("\x00", 1);
                                } else if (amp2On == false && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
                                    targetFileLoop2ndAmp.write("\x08", 1);
                                } else if (amp2On == false && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
                                    targetFileLoop2ndAmp.write("\x01", 1);
                                } else if (amp2On == false && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
                                    targetFileLoop2ndAmp.write("\x09", 1);
                                } else if (amp2On == false && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
                                    targetFileLoop2ndAmp.write("\x40", 1);
                                } else if (amp2On == false && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
                                    targetFileLoop2ndAmp.write("\x48", 1);
                                } else if (amp2On == false && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
                                    targetFileLoop2ndAmp.write("\x41", 1);
                                } else if (amp2On == false && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
                                    targetFileLoop2ndAmp.write("\x49", 1);
                                }

                                targetFileLoop2ndAmp.close();


                            }

                        }
                    }
                }
            }
        }
        sourceFile.close();
        targetFile.remove();
    }
}

bool MainWindow::poti(QFile &sourceFile, QFile &targetFile, int sourcePosition, int targetPosition) {

    float multiPoti = 0x7FFF;
    char floatIn[4];
    char hexOut1[1], hexOut2[1];

    sourceFile.seek(sourcePosition);
    sourceFile.read(floatIn, 4);

    // Parse 4 Bytes to float

    union {
      char chars[4];
      float f;
    } ufloat;

    for (int i = 0; i < 4; i++)
      ufloat.chars[3-i] = floatIn[i];
    float fPoti = ufloat.f;

    // Convert to int (2 Bytes)

    float floatCalculated = (fPoti * multiPoti);
    uint intToWrite = (int) floatCalculated;

    // Write to file
    hexOut1[0] = (intToWrite & 0xFF);
    hexOut2[0] = ((intToWrite >> 8) & 0xFF);
    targetFile.seek(targetPosition);
    targetFile.write(hexOut2, 1);
    targetFile.write(hexOut1, 1);
    return true;
}

bool MainWindow::potiDecibel(QFile &sourceFile, QFile &targetFile, int sourcePosition, int targetPosition) {

    char floatIn[4];
    char hexOut1[1], hexOut2[1];

    sourceFile.seek(sourcePosition);
    sourceFile.read(floatIn, 4);

    // Parse 4 Bytes to float

    union {
      char chars[4];
      float f;
    } ufloat;

    for (int i = 0; i < 4; i++)
      ufloat.chars[3-i] = floatIn[i];
    float fPoti = ufloat.f;

    // Convert to int (2 Bytes) - negative

    uint intToWrite = (int) 0x10000 - (0x25E8 * (fPoti));

    // Write to file
    hexOut1[0] = (intToWrite & 0xFF);
    hexOut2[0] = ((intToWrite >> 8) & 0xFF);
    targetFile.seek(targetPosition);
    targetFile.write(hexOut2, 1);
    targetFile.write(hexOut1, 1);
    return true;
}

bool MainWindow::potiReversed(QFile &sourceFile, QFile &targetFile, int sourcePosition, int targetPosition) {

    float multiPoti = 0x7FFF;
    char floatIn[4];
    char hexOut1[1], hexOut2[1];

    sourceFile.seek(sourcePosition);
    sourceFile.read(floatIn, 4);

    // Parse 4 Bytes to float

    union {
      char chars[4];
      float f;
    } ufloat;

    for (int i = 0; i < 4; i++)
      ufloat.chars[3-i] = floatIn[i];
    float fPoti = ufloat.f;

    // Convert to int (2 Bytes)

    float floatPreCalculated = (fPoti * multiPoti);
    float floatCalculated = (floatPreCalculated - multiPoti);
    uint intToWrite = (int) floatCalculated;

    // Write to file
    hexOut1[0] = (intToWrite & 0xFF);
    hexOut2[0] = ((intToWrite >> 8) & 0xFF);
    targetFile.seek(targetPosition);
    targetFile.write(hexOut2, 1);
    targetFile.write(hexOut1, 1);
    return true;
}

bool MainWindow::potiByte(QFile &sourceFile, QFile &targetFile, int sourcePosition, int targetPosition) {

    char floatIn[4];

    sourceFile.seek(sourcePosition);
    sourceFile.read(floatIn, 4);

    // Parse 4 Bytes to float

    union {
      char chars[4];
      float f;
    } ufloat;

    for (int i = 0; i < 4; i++)
      ufloat.chars[3-i] = floatIn[i];
    float fPoti = ufloat.f;

    // Convert to char (1 Byte)

    float floatCalculated = (fPoti * 255);
    char charToWrite[1] = { (char) floatCalculated };

    // Write to file
    targetFile.seek(targetPosition);
    targetFile.write(charToWrite, 1);
    return true;
}

void MainWindow::processChangeAmps() {

    for (int i = 0; i < listChkbxEditAmp.size(); i++) {
        if (listChkbxEditAmp.at(i)->isChecked() ) {
            switch (listCbEditAmp.at(i)->currentIndex())  {

                case 0:
                    ampOne[0] = '\x05';
                    break;
                case 1:
                    ampOne[0] = '\x06';
                    break;
                case 2:
                    ampOne[0] = '\x08';
                    break;
                case 3:
                    ampOne[0] = '\x0E';
                    break;
                case 4:
                    ampOne[0] = '\x14';
                    break;
                case 5:
                    ampOne[0] = '\x01';
                    break;
                case 6:
                    ampOne[0] = '\x02';
                    break;
                case 7:
                    ampOne[0] = '\x03';
                    break;
                case 8:
                    ampOne[0] = '\x04';
                    break;
                case 9:
                    ampOne[0] = '\x12';
                    break;
                case 10:
                    ampOne[0] = '\x00';
                    break;
                case 11:
                    ampOne[0] = '\x10';
                    break;
                case 12:
                    ampOne[0] = '\x11';
                    break;
                case 13:
                    ampOne[0] = '\x09';
                    break;
                case 14:
                    ampOne[0] = '\x0A';
                    break;
                case 15:
                    ampOne[0] = '\x55';
                    break;
                case 16:
                    ampOne[0] = '\x58';
                    break;
                case 17:
                    ampOne[0] = '\x0C';
                    break;
                case 18:
                    ampOne[0] = '\x0D';
                    break;
                case 19:
                    ampOne[0] = '\x15';
                    break;
                case 20:
                    ampOne[0] = '\x17';
                    break;
                case 21:
                    ampOne[0] = '\x0B';
                    break;
                case 22:
                    ampOne[0] = '\x19';
                    break;
                case 23:
                    ampOne[0] = '\x52';
                    break;
                case 24:
                    ampOne[0] = '\x5E';
                    break;
                case 25:
                    ampOne[0] = '\x61';
                    break;
                case 26:
                    ampOne[0] = '\x64';
                    break;
                case 27:
                    ampOne[0] = '\x67';
                    break;
                case 28:
                    ampOne[0] = '\x6A';
                    break;
                case 29:
                    ampOne[0] = '\x5B';
                    break;

                // Pre Amps
                case 30:
                    ampOne[0] = '\x20';
                    break;
                case 31:
                    ampOne[0] = '\x21';
                    break;
                case 32:
                    ampOne[0] = '\x23';
                    break;
                case 33:
                    ampOne[0] = '\x29';
                    break;
                case 34:
                    ampOne[0] = '\x2F';
                    break;
                case 35:
                    ampOne[0] = '\x1C';
                    break;
                case 36:
                    ampOne[0] = '\x1D';
                    break;
                case 37:
                    ampOne[0] = '\x1E';
                    break;
                case 38:
                    ampOne[0] = '\x1F';
                    break;
                case 39:
                    ampOne[0] = '\x2D';
                    break;
                case 40:
                    ampOne[0] = '\x1B';
                    break;
                case 41:
                    ampOne[0] = '\x2B';
                    break;
                case 42:
                    ampOne[0] = '\x2C';
                    break;
                case 43:
                    ampOne[0] = '\x24';
                    break;
                case 44:
                    ampOne[0] = '\x25';
                    break;
                case 45:
                    ampOne[0] = '\x56';
                    break;
                case 46:
                    ampOne[0] = '\x59';
                    break;
                case 47:
                    ampOne[0] = '\x27';
                    break;
                case 48:
                    ampOne[0] = '\x28';
                    break;
                case 49:
                    ampOne[0] = '\x30';
                    break;
                case 50:
                    ampOne[0] = '\x32';
                    break;
                case 51:
                    ampOne[0] = '\x26';
                    break;
                case 52:
                    ampOne[0] = '\x34';
                    break;
                case 53:
                    ampOne[0] = '\x53';
                    break;
                case 54:
                    ampOne[0] = '\x5F';
                    break;
                case 55:
                    ampOne[0] = '\x62';
                    break;
                case 56:
                    ampOne[0] = '\x65';
                    break;
                case 57:
                    ampOne[0] = '\x68';
                    break;
                case 58:
                    ampOne[0] = '\x6B';
                    break;
                case 59:
                    ampOne[0] = '\x5C';
                    break;

            }
        }
    }

    for (int i = 0; i < listChkbxEditCab.size(); i++) {
        if (listChkbxEditCab.at(i)->isChecked() ) {
            switch (listCbEditCab.at(i)->currentIndex())  {

                case 0:
                    cabOne[0] = '\x00';
                    break;
                case 1:
                    cabOne[0] = '\x01';
                    break;
                case 2:
                    cabOne[0] = '\x02';
                    break;
                case 3:
                    cabOne[0] = '\x03';
                    break;
                case 4:
                    cabOne[0] = '\x04';
                    break;
                case 5:
                    cabOne[0] = '\x05';
                    break;
                case 6:
                    cabOne[0] = '\x06';
                    break;
                case 7:
                    cabOne[0] = '\x08';
                    break;
                case 8:
                    cabOne[0] = '\x09';
                    break;
                case 9:
                    cabOne[0] = '\x0A';
                    break;
                case 10:
                    cabOne[0] = '\x0B';
                    break;
                case 11:
                    cabOne[0] = '\x0C';
                    break;
                case 12:
                    cabOne[0] = '\x0E';
                    break;
                case 13:
                    cabOne[0] = '\x11';
                    break;
                case 14:
                    cabOne[0] = '\x10';
                    break;
                case 15:
                    cabOne[0] = '\x0F';
                    break;
                case 16:
                    cabOne[0] = '\x12';
                    break;
                case 17:
                    CabOneOff = true;
                    break;

            }
        }
    }

    for (int i = 0; i < listChkbxEditMic.size(); i++) {
        if (listChkbxEditMic.at(i)->isChecked() ) {
            switch (listCbEditMic.at(i)->currentIndex())  {

                case 0:
                    micOne[0] = '\x00';
                    break;
                case 1:
                    micOne[0] = '\x01';
                    break;
                case 2:
                    micOne[0] = '\x02';
                    break;
                case 3:
                    micOne[0] = '\x03';
                    break;
                case 4:
                    micOne[0] = '\x04';
                    break;
                case 5:
                    micOne[0] = '\x05';
                    break;
                case 6:
                    micOne[0] = '\x06';
                    break;
                case 7:
                    micOne[0] = '\x07';
                    break;
            }
        }
    }
}

void MainWindow::modifyPresetFiles(QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];

    for (int i = 0; i < files.count(); i++) {
        QFile fileToModify(files[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

            if (ui->fiveChkbxEditFirstAmp->isChecked() || ui->desktopChkbxEditFirstAmp->isChecked() || ui->proChkbxEditFirstAmp->isChecked()) {

                // Check if first Amp is On
                fileToModify.seek(0x58);
                fileToModify.read(hexIn,1);
                if(hexIn[0] == 0x01) {
                    // Seek and Change first Amp Model

                    fileToModify.seek(0x53);
                    fileToModify.write(ampOne, maxSize);
                }
            }
            if (ui->fiveChkbxEditSecondAmp->isChecked() || ui->desktopChkbxEditSecondAmp->isChecked() || ui->proChkbxEditSecondAmp->isChecked()) {
                // Check if second Amp is On
                fileToModify.seek(0x15B);
                fileToModify.read(hexIn,1);
                if(hexIn[0] == 0x01) {
                    // Seek and Change first Amp Model

                    fileToModify.seek(0x153);
                    fileToModify.write(ampTwo, maxSize);
                }
            }
            if (ui->fiveChkbxEditFirstCab->isChecked() || ui->desktopChkbxEditFirstCab->isChecked() || ui->proChkbxEditFirstCab->isChecked()) {
                // Check if first Cab is On
                if(CabOneOff == true) {
                    fileToModify.seek(0x25B);
                    fileToModify.write("\x00", maxSize);
                }
                fileToModify.seek(0x25B);
                fileToModify.read(hexIn, 1);
                if(hexIn[0] == 0x01) {
                    // Seek and Change first Cab Model
                    fileToModify.seek(0x253);
                    fileToModify.write(cabOne, maxSize);
                }
            }
            if (ui->fiveChkbxEditSecondCab->isChecked() || ui->desktopChkbxEditSecondCab->isChecked() || ui->proChkbxEditSecondCab->isChecked()) {
                // Check if second Cab is On
                if(CabTwoOff == true) {
                    fileToModify.seek(0x35B);
                    fileToModify.write("\x00", maxSize);
                }
                fileToModify.seek(0x35B);
                fileToModify.read(hexIn, 1);
                if(hexIn[0] == 0x01) {
                    // Seek and Change first Cab Model
                    fileToModify.seek(0x353);
                    fileToModify.write(cabTwo, maxSize);
                }

            }
            if (ui->fiveChkbxEditFirstMic->isChecked() || ui->desktopChkbxEditFirstMic->isChecked() || ui->proChkbxEditFirstMic->isChecked()) {

                // Set first Microphone
                fileToModify.seek(0x1020);
                fileToModify.write(micOne, maxSize);
            }
            if (ui->fiveChkbxEditSecondMic->isChecked() || ui->desktopChkbxEditSecondMic->isChecked() || ui->proChkbxEditSecondMic->isChecked()) {
                // Set second Microphone
                fileToModify.seek(0x1021);
                fileToModify.write(micTwo, maxSize);

            }
            if (ui->fiveChkbxEditInputs->isChecked() || ui->desktopChkbxEditInputs->isChecked() || ui->proChkbxEditInputs->isChecked()) {
                fileToModify.seek(0x1026);
                fileToModify.write(sourceOne, maxSize);

                fileToModify.seek(0x1027);
                fileToModify.write(sourceTwo, maxSize);

                fileToModify.seek(0x0DFA);
                fileToModify.write(guitarIn, maxSize);
            }

            fileToModify.close();
        }
    }

}

void MainWindow::modifySetlistFiles(QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];

    for (int k = 0; k < files.count(); k++) {
        QFile fileToModify(files[k]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

            if (ui->fiveChkbxEditFirstAmp->isChecked() || ui->desktopChkbxEditFirstAmp->isChecked() || ui->proChkbxEditFirstAmp->isChecked()) {

                // Check if first Amp is On
                for (int i=0; i<64; i++) {
                fileToModify.seek(0x90 + (i * 0x001028));
                fileToModify.read(hexIn,1);
                if(hexIn[0] == 0x01) {
                    // Seek and Change first Amp Model
                        fileToModify.seek(0x8B + (i * 0x001028));
                        fileToModify.write(ampOne, maxSize);
                    }
                }
            }
            if (ui->fiveChkbxEditSecondAmp->isChecked() || ui->desktopChkbxEditSecondAmp->isChecked() || ui->proChkbxEditSecondAmp->isChecked()) {
                // Check if second Amp is On
                for (int i=0; i<64; i++) {
                fileToModify.seek(0x190  + (i * 0x001028));
                fileToModify.read(hexIn,1);
                if(hexIn[0] == 0x01) {
                    // Seek and Change second Amp Model
                        fileToModify.seek(0x018B + (i * 0x001028));
                        fileToModify.write(ampTwo, maxSize);
                    }
                }
            }
            if (ui->fiveChkbxEditFirstCab->isChecked() || ui->desktopChkbxEditFirstCab->isChecked() || ui->proChkbxEditFirstCab->isChecked()) {
                // Check if first Cab is On
                if(CabOneOff == true) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek(0x28B + (i * 0x001028));
                        fileToModify.write(cabOne, maxSize);
                    }
                }
                for (int i=0; i<64; i++) {
                fileToModify.seek(0x293 + (i * 0x001028));
                fileToModify.read(hexIn, 1);
                if(hexIn[0] == 0x01) {
                    // Seek and Change first Cab Model
                        fileToModify.seek(0x28B + (i * 0x001028));
                        fileToModify.write(cabOne, maxSize);
                    }
                }
            }
            if (ui->fiveChkbxEditSecondCab->isChecked() || ui->desktopChkbxEditSecondCab->isChecked() || ui->proChkbxEditSecondCab->isChecked()) {
                // Check if second Cab is On
                if(CabTwoOff == true) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek(0x38B + (i * 0x001028));
                        fileToModify.write(cabOne, maxSize);
                    }
                }
                for (int i=0; i<64; i++) {
                fileToModify.seek(0x393 + (i * 0x001028));
                fileToModify.read(hexIn, maxSize);
                if(hexIn[0] == 0x01) {
                    // Seek and Change second Cab Model
                        fileToModify.seek(0x38B + (i * 0x001028));
                        fileToModify.write(cabTwo, maxSize);
                    }
                }
            }
            if (ui->fiveChkbxEditFirstMic->isChecked() || ui->desktopChkbxEditFirstMic->isChecked() || ui->proChkbxEditFirstMic->isChecked()) {

                // Set first Microphone
                for (int i=0; i<64; i++) {
                    fileToModify.seek(0x1058 + (i * 0x001028));
                    fileToModify.write(micOne, maxSize);
                }
            }
            if (ui->fiveChkbxEditSecondMic->isChecked() || ui->desktopChkbxEditSecondMic->isChecked() || ui->proChkbxEditSecondMic->isChecked()) {
                // Set second Microphone
                for (int i=0; i<64; i++) {
                    fileToModify.seek(0x1059 + (i * 0x001028));
                    fileToModify.write(micTwo, maxSize);
                }
            }
            if (ui->fiveChkbxEditInputs->isChecked() || ui->desktopChkbxEditInputs->isChecked() || ui->proChkbxEditInputs->isChecked()) {
                for (int i=0; i<64; i++) {
                    fileToModify.seek(0x00105E + (i * 0x001028));
                    fileToModify.write(sourceOne, maxSize);

                    fileToModify.seek(0x00105F + (i * 0x001028));
                    fileToModify.write(sourceTwo, maxSize);

                    fileToModify.seek(0x000E32 + (i * 0x001028));
                    fileToModify.write(guitarIn, maxSize);
                }
            }


            fileToModify.close();
        }
    }
}

void MainWindow::modifyBundleFiles(QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];

    for (int k = 0; k < files.count(); k++) {
        QFile fileToModify(files[k]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

            if (ui->fiveChkbxEditFirstAmp->isChecked() || ui->desktopChkbxEditFirstAmp->isChecked() || ui->proChkbxEditFirstAmp->isChecked()) {

                // Check if first Amp is On
                // Content
                for (int j=0; j<8; j++) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek((0x0000B8 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.read(hexIn,1);
                        if(hexIn[0] == 0x01) {
                            // Seek and Change first Amp Model

                                fileToModify.seek((0x0000B3 + (j * 0x040A38)) + (i * 0x001028));
                                fileToModify.write(ampOne, maxSize);
                        }
                    }
                }
                // Setlist
                for (int i=0; i<7; i++) {
                    fileToModify.seek(0x0400B8 + (i * 0x040A38));
                    fileToModify.read(hexIn,1);
                    if(hexIn[0] == 0x01) {
                        // Seek and Change first Amp Model

                            fileToModify.seek(0x0400B3 + (i * 0x040A38));
                            fileToModify.write(ampOne, maxSize);
                    }
                }
            }

            if (ui->fiveChkbxEditSecondAmp->isChecked() || ui->desktopChkbxEditSecondAmp->isChecked() || ui->proChkbxEditSecondAmp->isChecked()) {
                // Check if second Amp is On
                // Content
                for (int j=0; j<8; j++) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek((0x0001B8 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.read(hexIn,1);
                        if(hexIn[0] == 0x01) {
                            // Seek and Change second Amp Model

                                fileToModify.seek((0x0001B3 + (j * 0x040A38)) + (i * 0x001028));
                                fileToModify.write(ampTwo, maxSize);
                        }
                    }
                }
                // Setlist
                for (int i=0; i<7; i++) {
                    fileToModify.seek(0x0401B8 + (i * 0x040A38));
                    fileToModify.read(hexIn,1);
                    if(hexIn[0] == 0x01) {
                        // Seek and Change second Amp Model

                            fileToModify.seek(0x0401B3 + (i * 0x040A38));
                            fileToModify.write(ampTwo, maxSize);
                    }
                }
            }
            if (ui->fiveChkbxEditFirstCab->isChecked() || ui->desktopChkbxEditFirstCab->isChecked() || ui->proChkbxEditFirstCab->isChecked()) {
                // Content
                // Check if first Cab is On
                if(CabOneOff == true) {

                    for (int j=0; j<8; j++) {
                        for (int i=0; i<64; i++) {
                            fileToModify.seek((0x0002B3 + (j * 0x040A38)) + (i * 0x001028));
                            fileToModify.write(cabOne, maxSize);
                        }
                    }
                }
                for (int j=0; j<8; j++) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek((0x0002BB + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.read(hexIn, maxSize);
                        if(hexIn[0] == 0x01) {
                            // Seek and Change first Cab Model
                                fileToModify.seek((0x0002B3 + (j * 0x040A38)) + (i * 0x001028));
                                fileToModify.write(cabOne, maxSize);
                        }
                    }
                }
                // Setlist

                // Check if first Cab is On
                if(CabOneOff == true) {
                    for (int i=0; i<7; i++) {
                        fileToModify.seek(0x0402B3 + (i * 0x040A38));
                        fileToModify.write(cabOne, maxSize);
                    }
                }
                for (int i=0; i<7; i++) {
                    fileToModify.seek(0x0402BB + (i * 0x040A38));
                    fileToModify.read(hexIn, maxSize);
                    if(hexIn[0] == 0x01) {
                        // Seek and Change first Cab Model
                            fileToModify.seek(0x0402B3 + (i * 0x040A38));
                            fileToModify.write(cabOne, maxSize);
                    }
                }
            }
            if (ui->fiveChkbxEditSecondCab->isChecked() || ui->desktopChkbxEditSecondCab->isChecked() || ui->proChkbxEditSecondCab->isChecked()) {
                // Content
                // Check if second Cab is On
                if(CabTwoOff == true) {

                    for (int j=0; j<8; j++) {
                        for (int i=0; i<64; i++) {
                            fileToModify.seek((0x0003B3 + (j * 0x040A38)) + (i * 0x001028));
                            fileToModify.write(cabTwo, maxSize);
                        }
                    }
                }
                for (int j=0; j<8; j++) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek((0x0003BB + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.read(hexIn, maxSize);
                        if(hexIn[0] == 0x01) {
                            // Seek and Change second Cab Model
                                fileToModify.seek((0x0003B3 + (j * 0x040A38)) + (i * 0x001028));
                                fileToModify.write(cabTwo, maxSize);
                        }
                    }
                }
                // Setlist

                // Check if second Cab is On
                if(CabTwoOff == true) {
                    for (int i=0; i<7; i++) {
                        fileToModify.seek(0x0403B3 + (i * 0x040A38));
                        fileToModify.write(cabTwo, maxSize);
                    }
                }
                for (int i=0; i<7; i++) {
                    fileToModify.seek(0x0403BB + (i * 0x040A38));
                    fileToModify.read(hexIn, maxSize);
                    if(hexIn[0] == 0x01) {
                        // Seek and Change second Cab Model
                            fileToModify.seek(0x0403B3 + (i * 0x040A38));
                            fileToModify.write(cabTwo, maxSize);
                    }
                }
            }
            if (ui->fiveChkbxEditFirstMic->isChecked() || ui->desktopChkbxEditFirstMic->isChecked() || ui->proChkbxEditFirstMic->isChecked()) {

                // Set first Microphone
                // Content
                for (int j=0; j<8; j++) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek((0x001080 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(micOne, maxSize);
                    }
                }
                // Setlist
                for (int i=0; i<7; i++) {
                    fileToModify.seek(0x041080 + (i * 0x040A38));
                    fileToModify.write(micOne, maxSize);
                }
            }
            if (ui->fiveChkbxEditSecondMic->isChecked() || ui->desktopChkbxEditSecondMic->isChecked() || ui->proChkbxEditSecondMic->isChecked()) {
                // Set second Microphone
                // Content
                for (int j=0; j<8; j++) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek((0x001081 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(micTwo, maxSize);
                    }
                }
                // Setlist
                for (int i=0; i<7; i++) {
                    fileToModify.seek(0x041081 + (i * 0x040A38));
                    fileToModify.write(micTwo, maxSize);
                }
            }
            if (ui->fiveChkbxEditInputs->isChecked() || ui->desktopChkbxEditInputs->isChecked() || ui->proChkbxEditInputs->isChecked()) {
                for (int j=0; j<8; j++) {
                    for (int i=0; i<64; i++) {
                        fileToModify.seek((0x001086 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(sourceOne, maxSize);

                        fileToModify.seek((0x001087 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(sourceTwo, maxSize);

                        fileToModify.seek((0x000E5A + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(guitarIn, maxSize);

                    }
                }
            }
            fileToModify.close();
        }
    }
}

void MainWindow::changePresetFilesAmps(QHash<char,char> &amps, QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];
    char hexOut[1];

    for (int i = 0; i < files.count(); i++) {
        QFile fileToModify(files[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

                    // Seek and Change first Amp Model

                    fileToModify.seek(0x53);
                    fileToModify.read(hexIn, maxSize);
                    fileToModify.seek(0x53);
                    hexOut[0] = amps.value(hexIn[0]);
                    fileToModify.write(hexOut, maxSize);

                    // Seek and Change first Amp Model

                    fileToModify.seek(0x153);
                    fileToModify.read(hexIn, maxSize);
                    fileToModify.seek(0x153);
                    hexOut[0] = amps.value(hexIn[0]);
                    fileToModify.write(hexOut, maxSize);

       }
       fileToModify.close();
    }
}

void MainWindow::changeBundleFilesAmps(QHash<char,char> &amps, QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];
    char hexOut[1];

    for (int i = 0; i < files.count(); i++) {
        QFile fileToModify(files[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

            // Content
            for (int j=0; j<8; j++) {
                for (int i=0; i<64; i++) {

                    fileToModify.seek((0x0000B3 + (j * 0x040A38)) + (i * 0x001028));
                    fileToModify.read(hexIn, maxSize);
                    fileToModify.seek((0x0000B3 + (j * 0x040A38)) + (i * 0x001028));
                    hexOut[0] = amps.value(hexIn[0]);
                    fileToModify.write(hexOut, maxSize);

                }
            }
            // Setlist
            for (int i=0; i<7; i++) {

                fileToModify.seek(0x0400B3 + (i * 0x040A38));
                fileToModify.read(hexIn, maxSize);
                fileToModify.seek(0x0400B3 + (i * 0x040A38));
                hexOut[0] = amps.value(hexIn[0]);
                fileToModify.write(hexOut, maxSize);

            }

            // Content
            for (int j=0; j<8; j++) {
                for (int i=0; i<64; i++) {

                    fileToModify.seek((0x0001B3 + (j * 0x040A38)) + (i * 0x001028));
                    fileToModify.read(hexIn, maxSize);
                    fileToModify.seek((0x0001B3 + (j * 0x040A38)) + (i * 0x001028));
                    hexOut[0] = amps.value(hexIn[0]);
                    fileToModify.write(hexOut, maxSize);

                }
            }
            // Setlist
            for (int i=0; i<7; i++) {

                fileToModify.seek(0x0401B3 + (i * 0x040A38));
                fileToModify.read(hexIn, maxSize);
                fileToModify.seek(0x0401B3 + (i * 0x040A38));
                hexOut[0] = amps.value(hexIn[0]);
                fileToModify.write(hexOut, maxSize);

            }
       }
        fileToModify.close();
    }
}

void MainWindow::changeSetlistFilesAmps(QHash<char,char> &amps, QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];
    char hexOut[1];

    for (int i = 0; i < files.count(); i++) {
        QFile fileToModify(files[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

            for (int i=0; i<64; i++) {

                fileToModify.seek(0x8B + (i * 0x001028));
                fileToModify.read(hexIn, maxSize);
                fileToModify.seek(0x8B + (i * 0x001028));
                hexOut[0] = amps.value(hexIn[0]);
                fileToModify.write(hexOut, maxSize);
            }

            for (int i=0; i<64; i++) {

                fileToModify.seek(0x18B + (i * 0x001028));
                fileToModify.read(hexIn, maxSize);
                fileToModify.seek(0x18B + (i * 0x001028));
                hexOut[0] = amps.value(hexIn[0]);
                fileToModify.write(hexOut, maxSize);

            }
       }
        fileToModify.close();
    }
}

void MainWindow::convertPresetFilesInputs(QHash<char, char> &inputs, QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];
    char hexOut[1];

    for (int i = 0; i < files.count(); i++) {
        QFile fileToModify(files[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

                    // Translate Input 1 and Input 2

                    fileToModify.seek(0x1026);
                    fileToModify.read(hexIn, maxSize);
                    if(inputs.contains(hexIn[0])) {
                        fileToModify.seek(0x1026);
                        hexOut[0] = inputs.value(hexIn[0]);
                        fileToModify.write(hexOut, maxSize);
                    }  else {
                        fileToModify.seek(0x1026);
                        fileToModify.write(sourceOne, maxSize);
                    }

                    fileToModify.seek(0x1027);
                    fileToModify.read(hexIn, maxSize);
                    if(inputs.contains(hexIn[0])) {
                        fileToModify.seek(0x1027);
                        hexOut[0] = inputs.value(hexIn[0]);
                        fileToModify.write(hexOut, maxSize);
                    }  else {
                        fileToModify.seek(0x1027);
                        fileToModify.write(sourceTwo, maxSize);
                    }

       }
       fileToModify.close();
    }
}

void MainWindow::convertBundleFilesInputs(QHash<char, char> &inputs, QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];
    char hexOut[1];

    for (int i = 0; i < files.count(); i++) {
        QFile fileToModify(files[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

            // Content
            for (int j=0; j<8; j++) {
                for (int i=0; i<64; i++) {

                    fileToModify.seek((0x001086 + (j * 0x040A38)) + (i * 0x001028));
                    fileToModify.read(hexIn, maxSize);
                    if(inputs.contains(hexIn[0])) {
                        fileToModify.seek((0x001086 + (j * 0x040A38)) + (i * 0x001028));
                        hexOut[0] = inputs.value(hexIn[0]);
                        fileToModify.write(hexOut, maxSize);
                    }  else {
                        fileToModify.seek((0x001086 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(sourceOne, maxSize);
                    }

                    fileToModify.seek((0x001087 + (j * 0x040A38)) + (i * 0x001028));
                    fileToModify.read(hexIn, maxSize);
                    if(inputs.contains(hexIn[0])) {
                        fileToModify.seek((0x001087 + (j * 0x040A38)) + (i * 0x001028));
                        hexOut[0] = inputs.value(hexIn[0]);
                        fileToModify.write(hexOut, maxSize);
                    }  else {
                        fileToModify.seek((0x001087 + (j * 0x040A38)) + (i * 0x001028));
                        fileToModify.write(sourceTwo, maxSize);
                    }

                }
            }
       }
        fileToModify.close();
    }
}

void MainWindow::convertSetlistFilesInputs(QHash<char, char> &inputs, QStringList files) {

    qint64 maxSize = 1;
    char hexIn[1];
    char hexOut[1];

    for (int i = 0; i < files.count(); i++) {
        QFile fileToModify(files[i]);
        if (fileToModify.open(QIODevice::ReadWrite)) {

            for (int i=0; i<64; i++) {

                fileToModify.seek(0x00105E + (i * 0x001028));
                fileToModify.read(hexIn, maxSize);
                if(inputs.contains(hexIn[0])) {
                    fileToModify.seek(0x00105E + (i * 0x001028));
                    hexOut[0] = inputs.value(hexIn[0]);
                    fileToModify.write(hexOut, maxSize);
                }  else {
                    fileToModify.seek(0x00105E + (i * 0x001028));
                    fileToModify.write(sourceOne, maxSize);
                }

                fileToModify.seek(0x00105F + (i * 0x001028));
                fileToModify.read(hexIn, maxSize);
                if(inputs.contains(hexIn[0])) {
                    fileToModify.seek(0x00105F + (i * 0x001028));
                    hexOut[0] = inputs.value(hexIn[0]);
                    fileToModify.write(hexOut, maxSize);
                }  else {
                    fileToModify.seek(0x00105F + (i * 0x001028));
                    fileToModify.write(sourceTwo, maxSize);
                }

            }
       }
        fileToModify.close();
    }
}


void MainWindow::runDesktop() {

    presetsPatched = 0;
    presetsModified = 0;

    getFiles(presetDirectory, fileFilter500);
    copyConvert(desktopPatchChkbxFive);
    processSettings("Desktop");
    processChangeAmps();
    convert("Desktop");

    convertPresetFilesInputs(Input500ToDesktop, fileList.at(0));
    convertBundleFilesInputs(Input500ToDesktop, fileList.at(1));
    convertSetlistFilesInputs(Input500ToDesktop, fileList.at(2));

    rename(desktopPatchChkbxFive, "Desktop");
    changeTextDesktop();

    getFiles(presetDirectory, fileFilterPro);
    copyConvert(desktopPatchChkbxPro);
    processSettings("Desktop");
    processChangeAmps();
    convert("Desktop");

    convertPresetFilesInputs(InputProToDesktop, fileList.at(0));
    convertBundleFilesInputs(InputProToDesktop, fileList.at(1));
    convertSetlistFilesInputs(InputProToDesktop, fileList.at(2));

    rename(desktopPatchChkbxPro, "Desktop");
    changeTextDesktop();

    if(ui->desktopChkbxModifyHbe->isChecked() || ui->desktopChkbxModifyHbb->isChecked() || ui->desktopChkbxModifyHbs->isChecked()) {

        getFiles(presetDirectory, fileFilterDesktop);
        copyModify();
        processSettings("Desktop");
        processChangeAmps();
        modify("Desktop");
        changeAmps("Desktop");
        changeTextDesktop();

    }
}

void MainWindow::run300() {

    presetsPatched = 0;
    presetsModified = 0;

    getFiles(presetDirectory, fileFilter500);
    copyModify();
    convert("300");

    getFiles(presetDirectory, fileFilterDesktop);
    copyModify();
    convert("300");

    getFiles(presetDirectory, fileFilterPro);
    copyModify();
    convert("300");
    changeText300();
}

void MainWindow::run500() {

    presetsPatched = 0;
    presetsModified = 0;

    getFiles(presetDirectory, fileFilterDesktop);
    copyConvert(fivePatchChkbxDesktop);
    processSettings("500");
    processChangeAmps();
    convert("500");

    convertPresetFilesInputs(InputDesktopTo500, fileList.at(0));
    convertBundleFilesInputs(InputDesktopTo500, fileList.at(1));
    convertSetlistFilesInputs(InputDesktopTo500, fileList.at(2));

    rename(fivePatchChkbxDesktop, "500");
    changeText500();

    getFiles(presetDirectory, fileFilterPro);
    copyConvert(fivePatchChkbxPro);
    processSettings("500");
    processChangeAmps();
    convert("500");

    convertPresetFilesInputs(InputProTo500, fileList.at(0));
    convertBundleFilesInputs(InputProTo500, fileList.at(1));
    convertSetlistFilesInputs(InputProTo500, fileList.at(2));

    rename(fivePatchChkbxPro, "500");
    changeText500();

    if(ui->fiveChkbxModifyH5e->isChecked() || ui->fiveChkbxModifyH5b->isChecked() || ui->fiveChkbxModifyH5s->isChecked()) {

        getFiles(presetDirectory, fileFilter500);
        copyModify();
        processSettings("500");
        processChangeAmps();
        modify("500");
        changeAmps("500");
        changeText500();

    }
}

void MainWindow::runPro() {

    presetsPatched = 0;
    presetsModified = 0;

    getFiles(presetDirectory, fileFilter500);
    copyConvert(proPatchChkbxFive);
    processSettings("Pro");
    processChangeAmps();
    convert("Pro");

    convertPresetFilesInputs(Input500ToPro, fileList.at(0));
    convertBundleFilesInputs(Input500ToPro, fileList.at(1));
    convertSetlistFilesInputs(Input500ToPro, fileList.at(2));

    rename(proPatchChkbxFive, "Pro");
    changeTextPro();

    getFiles(presetDirectory, fileFilterDesktop);
    copyConvert(proPatchChkbxDesktop);
    processSettings("Pro");
    processChangeAmps();
    convert("Pro");

    convertPresetFilesInputs(InputDesktopToPro, fileList.at(0));
    convertBundleFilesInputs(InputDesktopToPro, fileList.at(1));
    convertSetlistFilesInputs(InputDesktopToPro, fileList.at(2));

    rename(proPatchChkbxDesktop, "Pro");
    changeTextPro();

    if(ui->proChkbxModifyHre->isChecked() || ui->proChkbxModifyHrb->isChecked() || ui->proChkbxModifyHrs->isChecked()) {

        getFiles(presetDirectory, fileFilterPro);
        copyModify();
        processSettings("Pro");
        processChangeAmps();
        modify("Pro");
        changeAmps("Pro");
        changeTextDesktop();

    }
}
