//
//  convert.m
//  PODHD Converter
//
//  Created by xen on 5/3/12.
//  Copyright (c) 2012 www.jzab.de. All rights reserved.
//

#import "convert.h"

NSString * const H5E_EXTENSION = @"h5e";
NSString * const H5B_EXTENSION = @"h5b";
NSString * const H5S_EXTENSION = @"h5s";

NSString * const HRE_EXTENSION = @"hre";
NSString * const HRB_EXTENSION = @"hrb";
NSString * const HRS_EXTENSION = @"hrs";

NSString * const HBE_EXTENSION = @"hbe";
NSString * const HBB_EXTENSION = @"hbb";
NSString * const HBS_EXTENSION = @"hbs";

NSString * const H4E_EXTENSION = @"h4e";
NSString * const H3E_EXTENSION = @"h3e";
size_t length;

NSURL *presetFromDirectory;

NSUInteger presetsPatched;
NSUInteger presetsMoved;

NSString *absolutePathPresets;
NSString *backupPath;

NSArray *onlyH5eFiles;
NSArray *onlyH5bFiles;
NSArray *onlyH5sFiles;

NSArray *onlyHbeFiles;
NSArray *onlyHbbFiles;
NSArray *onlyHbsFiles;

NSArray *onlyHreFiles;
NSArray *onlyHrbFiles;
NSArray *onlyHrsFiles;

NSArray *extensionH5e;
NSArray *extensionH5b;
NSArray *extensionH5s;

NSArray *extensionHre;
NSArray *extensionHrb;
NSArray *extensionHrs;

NSArray *extensionHbe;
NSArray *extensionHbb;
NSArray *extensionHbs;

NSArray *extensionH4e;
NSArray *extensionH3e;

NSMutableData *sourceOne = nil;
NSMutableData *sourceTwo = nil;
NSMutableData *guitarIn = nil;

@implementation convert

// // Initializise Constants
// + (void)initialize {
//     extensionH5e = [NSArray arrayWithObjects:@"h5e", nil];
//     extensionHbe = [NSArray arrayWithObjects:@"hbe", nil];
// }

- (void) initialize {
    
    length = 1; //string literals have implicit trailing '\0'
    
    //NSLog(@"%zu", length);
    
    sourceOne = [[NSMutableData alloc] initWithBytes:"\x01" length:length];
    sourceTwo = [[NSMutableData alloc] initWithBytes:"\x00" length:length];
    guitarIn = [[NSMutableData alloc] initWithBytes:"\x00" length:length];
    
    extensionH5e = [[NSArray alloc] initWithObjects:@"h5e", (void *)nil];
    extensionH5b = [[NSArray alloc] initWithObjects:@"h5b", (void *)nil];
    extensionH5s = [[NSArray alloc] initWithObjects:@"h5s", (void *)nil];
    
    extensionHre = [[NSArray alloc] initWithObjects:@"hre", (void *)nil];
    extensionHrb = [[NSArray alloc] initWithObjects:@"hrb", (void *)nil];
    extensionHrs = [[NSArray alloc] initWithObjects:@"hrs", (void *)nil];

    extensionHbe = [[NSArray alloc] initWithObjects:@"hbe", (void *)nil];
    extensionHbb = [[NSArray alloc] initWithObjects:@"hbb", (void *)nil];
    extensionHbs = [[NSArray alloc] initWithObjects:@"hbs", (void *)nil];
    
    extensionH4e = [[NSArray alloc] initWithObjects:@"h4e", (void *)nil];
    extensionH3e = [[NSArray alloc] initWithObjects:@"h3e", (void *)nil];
    

    [sourceOne retain];
    [sourceTwo retain];
    [guitarIn retain];
    
    [extensionH5e retain];
    [extensionHbe retain];
    [extensionH5b retain];
    [extensionHbb retain];
    [extensionH5s retain];
    [extensionHbs retain];
    [extensionH4e retain];
    [extensionH3e retain];
}

- (void) destruct {
    
    [sourceOne release];
    sourceOne = nil;
    
    [sourceTwo release];
    sourceTwo = nil;
    
    [guitarIn release];
    guitarIn = nil;

}

- (IBAction)browseButton:(id)sender {
    
    // Create a File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Set array of file types
    //NSArray *fileTypesArray;
    //fileTypesArray = [NSArray arrayWithObjects:@"h5e", @"hbe", nil];
    
    // Enable options in the dialog.
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:NO];
    //[openDlg setAllowedFileTypes:fileTypesArray];
    //[openDlg setAllowsMultipleSelection:TRUE];
    
    // Display the dialog box.  If the OK pressed,
    // process the files.
    if ( [openDlg runModal] == NSFileHandlingPanelOKButton ) {
        
        // Gets list of all files selected
        //NSArray *files = [openDlg URLs];
        
        // Get choosen Directory as NSURL.
        presetFromDirectory = [[openDlg URLs] objectAtIndex:0];
        [presetFromDirectory retain];
        
        // Get choosen Directory as String (for setting Label).
        absolutePathPresets = [[[openDlg URLs] objectAtIndex:0] path];
        [presetFromDirectoryLabel setStringValue:absolutePathPresets];
    }
}

- (IBAction)browseButton300:(id)sender {
    
    // Create a File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Set array of file types
    //NSArray *fileTypesArray;
    //fileTypesArray = [NSArray arrayWithObjects:@"h5e", @"hbe", nil];
    
    // Enable options in the dialog.
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:NO];
    //[openDlg setAllowedFileTypes:fileTypesArray];
    //[openDlg setAllowsMultipleSelection:TRUE];
    
    // Display the dialog box.  If the OK pressed,
    // process the files.
    if ( [openDlg runModal] == NSFileHandlingPanelOKButton ) {
        
        // Gets list of all files selected
        //NSArray *files = [openDlg URLs];
        
        // Get choosen Directory as NSURL.
        presetFromDirectory = [[openDlg URLs] objectAtIndex:0];
        [presetFromDirectory retain];
        
        // Get choosen Directory as String (for setting Label).
        absolutePathPresets = [[[openDlg URLs] objectAtIndex:0] path];
        [presetFromDirectoryLabel300 setStringValue:absolutePathPresets];
    }
}

- (void) processAdvancedTab {
    if ([chkbxEditPresets state] == NSOnState) {
        switch ([cbInputSourceOne indexOfSelectedItem]) {
            case 0:
                if (sourceOne) {
                    [sourceOne release];
                }
                sourceOne = [[NSMutableData alloc] initWithBytes:"\x01" length:length];
                //[sourceOne setData:[[NSData alloc] initWithBytes:"\x01" length:1]];
                [sourceOne retain];
                
                //NSLog(@"%p", [sourceOne bytes]);
                //NSLog(@"bytes in hex: %@", [sourceOne description]);
                break;
            case 1:
                if (sourceOne) {
                    [sourceOne release];
                }
                sourceOne = [[NSMutableData alloc] initWithBytes:"\x02" length:length];
                [sourceOne retain];
                break;


        }
        
        switch ([cbInputSourceTwo indexOfSelectedItem]) {
            case 0:
                if (sourceTwo) {
                    [sourceTwo release];
                }
                sourceTwo = [[NSMutableData alloc] initWithBytes:"\x00" length:length];
                [sourceTwo retain];
            case 1:
                if (sourceTwo) {
                    [sourceTwo release];
                }
                sourceTwo = [[NSMutableData alloc] initWithBytes:"\x01" length:length];
                [sourceTwo retain];
                break;
            case 2:
                if (sourceTwo) {
                    [sourceTwo release];
                }
                sourceTwo = [[NSMutableData alloc] initWithBytes:"\x02" length:length];
                [sourceTwo retain];
                break;
        }
        
        switch ([cbGuitarIn indexOfSelectedItem]) {
            case 0:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x00" length:length];
                [guitarIn retain];
                break;
            case 1:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x01" length:length];
                [guitarIn retain];
                break;
            case 2:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x02" length:length];
                [guitarIn retain];
                break;     
            case 3:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x03" length:length];
                [guitarIn retain];
                break;
            case 4:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x04" length:length];
                [guitarIn retain];
                break;
            case 5:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x05" length:length];
                [guitarIn retain];
                break;    
            case 6:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x06" length:length];
                [guitarIn retain];
                break;
            case 7:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x07" length:length];
                [guitarIn retain];
                break;
            case 8:
                if (guitarIn) {
                    [guitarIn release];
                }
                guitarIn = [[NSMutableData alloc] initWithBytes:"\x08" length:length];
                [guitarIn retain];
                break;
        }
    }
}

- (IBAction)enteredDirectory:(id)sender {
    presetFromDirectory = [[NSURL alloc] initWithString:[presetFromDirectoryLabel stringValue]];
}

- (IBAction)enteredDirectory300:(id)sender {
    presetFromDirectory = [[NSURL alloc] initWithString:[presetFromDirectoryLabel300 stringValue]];
}

- (void) getFiles:(NSURL *)pathOfPresetDirectory pressedFrom:(NSString *)model {
    
    if ([model isEqualToString:@"Desktop"]) {
        
        // Fetch Preset Files from Directory as Array
        NSArray *contentsOfDirectory = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[pathOfPresetDirectory path] error:nil];
        onlyH5eFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@", extensionH5e]];
        onlyHbeFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@",  extensionHbe]];
        onlyH5bFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@",  extensionH5b]];
        onlyHbbFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@",  extensionHbb]];
        onlyH5sFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@",  extensionH5s]];
        onlyHbsFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@",  extensionHbs]];
        [onlyH5eFiles retain];
        [onlyHbeFiles retain];
        [onlyH5bFiles retain];
        [onlyHbbFiles retain];
        [onlyH5sFiles retain];
        [onlyHbsFiles retain];
    } else if ([model isEqualToString:@"300"]) {
        NSArray *contentsOfDirectory = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[pathOfPresetDirectory path] error:nil];
        onlyH5eFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@", extensionH5e]];
        onlyHbeFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@", extensionHbe]];
        onlyHreFiles = [contentsOfDirectory filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"pathExtension IN %@", extensionHre]];
    }

}

- (void) modify:(NSURL *)path pressedFrom:(NSString *) model {
    
        if ([model isEqualToString:@"Desktop"]) {
            
            presetsPatched = 0;
            
            @try {
                if ([chkbxPatchH5e state] == NSOnState) {
                    [self modifyPatchFiles:onlyH5eFiles fromPath:path];
                    presetsPatched = [onlyH5eFiles count];
                    //[onlyH5eFiles release];
                }
                if ([chkbxPatchHbe state] == NSOnState) {
                    [self modifyPatchFiles:onlyHbeFiles fromPath:path];
                    presetsPatched = presetsPatched + [onlyHbeFiles count];
                    //[onlyHbeFiles release];
                }
                if ([chkbxPatchH5b state] == NSOnState) {
                    [self modifyBundleFiles:onlyH5bFiles fromPath:path];
                    presetsPatched = presetsPatched + [onlyH5bFiles count];
                    //[onlyH5eFiles release];
                }
                if ([chkbxPatchHbb state] == NSOnState) {
                    [self modifyBundleFiles:onlyHbbFiles fromPath:path];
                    presetsPatched = presetsPatched + [onlyHbbFiles count];
                    //[onlyHbeFiles release];
                }
                if ([chkbxPatchH5s state] == NSOnState) {
                    [self modifySetlistFiles:onlyH5sFiles fromPath:path];
                    presetsPatched = presetsPatched + [onlyH5sFiles count];
                    //[onlyH5eFiles release];
                }
                if ([chkbxPatchHbs state] == NSOnState) {
                    [self modifySetlistFiles:onlyHbsFiles fromPath:path];
                    presetsPatched = presetsPatched + [onlyHbsFiles count];
                    //[onlyHbeFiles release];
                }
            }
            @catch (NSException *exception) {
                
                NSLog(@"main: Caught %@: %@", [exception name], [exception reason]);
                
            }
            @finally {
                //[onlyH5eFiles release];
                //[onlyHbeFiles release];
                //[onlyH5bFiles release];
                //[onlyHbbFiles release];
                //[onlyH5sFiles release];
                //[onlyHbsFiles release];
            }        
        } else if ([model isEqualToString:@"300"]) {
            
            presetsPatched = 0;
            
            @try {
                if ([chkbxPatchH3e state] == NSOnState) {
                    [self modifyPatchFiles300:onlyH5eFiles fromPath:path toExtension:(NSString *)H3E_EXTENSION];
                    [self modifyPatchFiles300:onlyHbeFiles fromPath:path toExtension:(NSString *)H3E_EXTENSION];
                    [self modifyPatchFiles300:onlyHreFiles fromPath:path toExtension:(NSString *)H3E_EXTENSION];
                    presetsPatched = [onlyH5eFiles count] + [onlyHbeFiles count] + [onlyHreFiles count];
                    //[onlyHbeFiles release];
                }
                if ([chkbxPatchH4e state] == NSOnState) {
                    [self modifyPatchFiles300:onlyH5eFiles fromPath:path toExtension:(NSString *)H4E_EXTENSION];
                    [self modifyPatchFiles300:onlyHbeFiles fromPath:path toExtension:(NSString *)H4E_EXTENSION];
                    [self modifyPatchFiles300:onlyHreFiles fromPath:path toExtension:(NSString *)H4E_EXTENSION];
                    presetsPatched = [onlyH5eFiles count] + [onlyHbeFiles count] + [onlyHreFiles count];
                    //[onlyH5eFiles release];
                }
            }
            @catch (NSException *exception) {
                
                NSLog(@"main: Caught %@: %@", [exception name], [exception reason]);
                
            }
        }
}


- (void) modifyPatchFiles: (NSArray *) presetFiles fromPath:(NSURL *)path {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    @autoreleasepool {
        
        for (int i = 0; i < [presetFiles count] ; i = i+1) {
            
            NSString *pathToPreset;
            
            //NSLog(@"%p", [sourceOne bytes]);
            //NSLog(@"sourceOne - bytes in hex: %@", [sourceOne description]);
            //NSLog(@"%p", [sourceTwo bytes]);
            //NSLog(@"sourceTwo - bytes in hex: %@", [sourceTwo description]);
            //NSLog(@"%p", [guitarIn bytes]);
            //NSLog(@"guitarIn - bytes in hex: %@", [guitarIn description]);
        
            NSString *presetName = [presetFiles objectAtIndex:i];
            pathToPreset = [[path path] stringByAppendingPathComponent:presetName];

            //NSLog(@"File to be modified: %@", fullPathPreset);
            
            NSData *data000B = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data000C = [[NSData alloc] initWithBytes:"\x01" length:length]; 
            NSData *data000D = [[NSData alloc] initWithBytes:"\x06" length:length];
            NSData *data0013 = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data0014 = [[NSData alloc] initWithBytes:"\x02" length:length];
            NSData *data0015 = [[NSData alloc] initWithBytes:"\x02" length:length];
            NSData *data0DFA = [[NSData alloc] initWithBytes:"\x07" length:length];
            NSData *data1026 = [[NSData alloc] initWithBytes:"\x01" length:length];
            NSData *data1027 = [[NSData alloc] initWithBytes:"\x00" length:length];
        
            NSFileHandle *modifyFile = [NSFileHandle fileHandleForUpdatingAtPath: pathToPreset];
        
            if (modifyFile == nil)
                NSLog(@"Failed to open file");
        
            [modifyFile seekToFileOffset: 0x000B];
            [modifyFile writeData: data000B];

            [modifyFile seekToFileOffset: 0x000C];
            [modifyFile writeData: data000C];
            
            [modifyFile seekToFileOffset: 0x000D];
            [modifyFile writeData: data000D];
            
            [modifyFile seekToFileOffset: 0x0013];
            [modifyFile writeData: data0013];
            
            [modifyFile seekToFileOffset: 0x0014];
            [modifyFile writeData: data0014];
            
            [modifyFile seekToFileOffset: 0x0015];
            [modifyFile writeData: data0015];
            
            [modifyFile seekToFileOffset: 0x0DFA];
            [modifyFile writeData: guitarIn];
            
            [modifyFile seekToFileOffset: 0x1026];
            [modifyFile writeData: sourceOne];
            
            [modifyFile seekToFileOffset: 0x1027];
            [modifyFile writeData: sourceTwo];
            
            // Read data for testing purpose
            //databuffer = [modifyFile readDataOfLength: 1];
            //NSLog (@"Data = %@", databuffer);
            
            [data000B release];
            data000B = nil;
            
            [data000C release];
            data000C = nil;
            
            [data000D release];
            data000D = nil;
            
            [data0013 release];
            data0013 = nil;
            
            [data0014 release];
            data0014 = nil;
            
            [data0015 release];
            data0015 = nil;
            
            [data0DFA release];
            data0DFA = nil;
            
            [data1026 release];
            data1026 = nil;
            
            [data1027 release];
            data1027 = nil;
                    
            [modifyFile closeFile];
        }
    }
    [pool release];        
} 

- (void) modifyPatchFiles300: (NSArray *) presetFiles fromPath:(NSURL *)path toExtension:(NSString *)toExtension {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
                        
    const char h3eStructureChar[] = {
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
            
    size_t lenH3eStructure = sizeof(h3eStructureChar)/sizeof(h3eStructureChar[0]);
    NSData *h3eStructure = [NSData dataWithBytes:h3eStructureChar length:lenH3eStructure];
                        
    bool ampOn = false, reverbPrePost = false, hasNoiseGate = false, hasWah = false;
    bool amp2On = false;
            
    bool hasDualamp = false;
            
    // Bytes to define FX status
            
    NSData *fxOffPre = [[NSData alloc] initWithBytes:"\x00" length:length];
    NSData *fxOffPost = [[NSData alloc] initWithBytes:"\x02" length:length]; 
    NSData *fxOnPre = [[NSData alloc] initWithBytes:"\x04" length:length];
    NSData *fxOnPost = [[NSData alloc] initWithBytes:"\x06" length:length];
    
    NSData *databuffer;
            
    // HashTables for Amp / Cab / FX Mapping
            
    NSMapTable *Amps = [NSMapTable mapTableWithStrongToStrongObjects];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x00" length:length] forKey:[[NSData alloc] initWithBytes:"\x05" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x10" length:length] forKey:[[NSData alloc] initWithBytes:"\x06" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x01" length:length] forKey:[[NSData alloc] initWithBytes:"\x08" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x0E" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x03" length:length] forKey:[[NSData alloc] initWithBytes:"\x14" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x04" length:length] forKey:[[NSData alloc] initWithBytes:"\x01" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x11" length:length] forKey:[[NSData alloc] initWithBytes:"\x02" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x05" length:length] forKey:[[NSData alloc] initWithBytes:"\x03" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x12" length:length] forKey:[[NSData alloc] initWithBytes:"\x04" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x06" length:length] forKey:[[NSData alloc] initWithBytes:"\x12" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x07" length:length] forKey:[[NSData alloc] initWithBytes:"\x00" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x08" length:length] forKey:[[NSData alloc] initWithBytes:"\x10" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x09" length:length] forKey:[[NSData alloc] initWithBytes:"\x11" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x13" length:length] forKey:[[NSData alloc] initWithBytes:"\x09" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0A" length:length] forKey:[[NSData alloc] initWithBytes:"\x0A" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x16" length:length] forKey:[[NSData alloc] initWithBytes:"\x55" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x17" length:length] forKey:[[NSData alloc] initWithBytes:"\x58" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x14" length:length] forKey:[[NSData alloc] initWithBytes:"\x0C" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0B" length:length] forKey:[[NSData alloc] initWithBytes:"\x0D" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0C" length:length] forKey:[[NSData alloc] initWithBytes:"\x15" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0D" length:length] forKey:[[NSData alloc] initWithBytes:"\x17" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0E" length:length] forKey:[[NSData alloc] initWithBytes:"\x0B" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0F" length:length] forKey:[[NSData alloc] initWithBytes:"\x19" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x15" length:length] forKey:[[NSData alloc] initWithBytes:"\x52" length:length]];    
    [Amps setObject:[[NSData alloc] initWithBytes:"\x18" length:length] forKey:[[NSData alloc] initWithBytes:"\x5E" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x19" length:length] forKey:[[NSData alloc] initWithBytes:"\x61" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x1A" length:length] forKey:[[NSData alloc] initWithBytes:"\x64" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x1B" length:length] forKey:[[NSData alloc] initWithBytes:"\x67" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x1C" length:length] forKey:[[NSData alloc] initWithBytes:"\x6A" length:length]];    
    [Amps setObject:[[NSData alloc] initWithBytes:"\x1D" length:length] forKey:[[NSData alloc] initWithBytes:"\x5B" length:length]];
            
    // Pre Models
    [Amps setObject:[[NSData alloc] initWithBytes:"\x00" length:length] forKey:[[NSData alloc] initWithBytes:"\x20" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x10" length:length] forKey:[[NSData alloc] initWithBytes:"\x21" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x01" length:length] forKey:[[NSData alloc] initWithBytes:"\x23" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x29" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x03" length:length] forKey:[[NSData alloc] initWithBytes:"\x2F" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x04" length:length] forKey:[[NSData alloc] initWithBytes:"\x1C" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x11" length:length] forKey:[[NSData alloc] initWithBytes:"\x1D" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x05" length:length] forKey:[[NSData alloc] initWithBytes:"\x1E" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x12" length:length] forKey:[[NSData alloc] initWithBytes:"\x1F" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x06" length:length] forKey:[[NSData alloc] initWithBytes:"\x2D" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x07" length:length] forKey:[[NSData alloc] initWithBytes:"\x1B" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x08" length:length] forKey:[[NSData alloc] initWithBytes:"\x2B" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x09" length:length] forKey:[[NSData alloc] initWithBytes:"\x2C" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x13" length:length] forKey:[[NSData alloc] initWithBytes:"\x24" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0A" length:length] forKey:[[NSData alloc] initWithBytes:"\x25" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x16" length:length] forKey:[[NSData alloc] initWithBytes:"\x56" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x17" length:length] forKey:[[NSData alloc] initWithBytes:"\x59" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x14" length:length] forKey:[[NSData alloc] initWithBytes:"\x27" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0B" length:length] forKey:[[NSData alloc] initWithBytes:"\x28" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0C" length:length] forKey:[[NSData alloc] initWithBytes:"\x30" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0D" length:length] forKey:[[NSData alloc] initWithBytes:"\x32" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0E" length:length] forKey:[[NSData alloc] initWithBytes:"\x26" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x0F" length:length] forKey:[[NSData alloc] initWithBytes:"\x34" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x15" length:length] forKey:[[NSData alloc] initWithBytes:"\x53" length:length]];    
    [Amps setObject:[[NSData alloc] initWithBytes:"\x18" length:length] forKey:[[NSData alloc] initWithBytes:"\x5F" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x19" length:length] forKey:[[NSData alloc] initWithBytes:"\x62" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x1A" length:length] forKey:[[NSData alloc] initWithBytes:"\x65" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x1B" length:length] forKey:[[NSData alloc] initWithBytes:"\x68" length:length]];
    [Amps setObject:[[NSData alloc] initWithBytes:"\x1C" length:length] forKey:[[NSData alloc] initWithBytes:"\x6B" length:length]];    
    [Amps setObject:[[NSData alloc] initWithBytes:"\x19" length:length] forKey:[[NSData alloc] initWithBytes:"\x5C" length:length]];
            
    NSMapTable *PreAmps = [NSMapTable mapTableWithStrongToStrongObjects];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x00" length:length] forKey:[[NSData alloc] initWithBytes:"\x20" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x10" length:length] forKey:[[NSData alloc] initWithBytes:"\x21" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x01" length:length] forKey:[[NSData alloc] initWithBytes:"\x23" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x29" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x03" length:length] forKey:[[NSData alloc] initWithBytes:"\x2F" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x04" length:length] forKey:[[NSData alloc] initWithBytes:"\x1C" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x11" length:length] forKey:[[NSData alloc] initWithBytes:"\x1D" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x05" length:length] forKey:[[NSData alloc] initWithBytes:"\x1E" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x12" length:length] forKey:[[NSData alloc] initWithBytes:"\x1F" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x06" length:length] forKey:[[NSData alloc] initWithBytes:"\x2D" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x07" length:length] forKey:[[NSData alloc] initWithBytes:"\x1B" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x08" length:length] forKey:[[NSData alloc] initWithBytes:"\x2B" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x09" length:length] forKey:[[NSData alloc] initWithBytes:"\x2C" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x13" length:length] forKey:[[NSData alloc] initWithBytes:"\x24" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x0A" length:length] forKey:[[NSData alloc] initWithBytes:"\x25" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x16" length:length] forKey:[[NSData alloc] initWithBytes:"\x56" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x17" length:length] forKey:[[NSData alloc] initWithBytes:"\x59" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x14" length:length] forKey:[[NSData alloc] initWithBytes:"\x27" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x0B" length:length] forKey:[[NSData alloc] initWithBytes:"\x28" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x0C" length:length] forKey:[[NSData alloc] initWithBytes:"\x30" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x0D" length:length] forKey:[[NSData alloc] initWithBytes:"\x32" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x0E" length:length] forKey:[[NSData alloc] initWithBytes:"\x26" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x0F" length:length] forKey:[[NSData alloc] initWithBytes:"\x34" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x15" length:length] forKey:[[NSData alloc] initWithBytes:"\x53" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x18" length:length] forKey:[[NSData alloc] initWithBytes:"\x5F" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x19" length:length] forKey:[[NSData alloc] initWithBytes:"\x62" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x1A" length:length] forKey:[[NSData alloc] initWithBytes:"\x65" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x1B" length:length] forKey:[[NSData alloc] initWithBytes:"\x68" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x1C" length:length] forKey:[[NSData alloc] initWithBytes:"\x6B" length:length]];
    [PreAmps setObject:[[NSData alloc] initWithBytes:"\x19" length:length] forKey:[[NSData alloc] initWithBytes:"\x5C" length:length]];
    
    // Cabs
    
    NSMapTable *Cabs = [NSMapTable mapTableWithStrongToStrongObjects];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x08" length:length] forKey:[[NSData alloc] initWithBytes:"\x00" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x03" length:length] forKey:[[NSData alloc] initWithBytes:"\x01" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x07" length:length] forKey:[[NSData alloc] initWithBytes:"\x02" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x06" length:length] forKey:[[NSData alloc] initWithBytes:"\x03" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x04" length:length] forKey:[[NSData alloc] initWithBytes:"\x04" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x09" length:length] forKey:[[NSData alloc] initWithBytes:"\x05" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x01" length:length] forKey:[[NSData alloc] initWithBytes:"\x06" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x0A" length:length] forKey:[[NSData alloc] initWithBytes:"\x08" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x05" length:length] forKey:[[NSData alloc] initWithBytes:"\x09" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x0E" length:length] forKey:[[NSData alloc] initWithBytes:"\x0A" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x10" length:length] forKey:[[NSData alloc] initWithBytes:"\x0B" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x0C" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x0B" length:length] forKey:[[NSData alloc] initWithBytes:"\x0E" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x0C" length:length] forKey:[[NSData alloc] initWithBytes:"\x11" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x0F" length:length] forKey:[[NSData alloc] initWithBytes:"\x10" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x0D" length:length] forKey:[[NSData alloc] initWithBytes:"\x0F" length:length]];
    [Cabs setObject:[[NSData alloc] initWithBytes:"\x11" length:length] forKey:[[NSData alloc] initWithBytes:"\x12" length:length]];
    
    // Effects
    
    // Dyn
    
    NSMapTable *Dyn1 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x12" length:length] forKey:[[NSData alloc] initWithBytes:"\x12" length:length]];
    [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x13" length:length] forKey:[[NSData alloc] initWithBytes:"\x0B" length:length]];
    [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x14" length:length] forKey:[[NSData alloc] initWithBytes:"\x0C" length:length]];
    [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x16" length:length] forKey:[[NSData alloc] initWithBytes:"\x0F" length:length]];
    [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x5F" length:length] forKey:[[NSData alloc] initWithBytes:"\x13" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x14" length:length] forKey:[[NSData alloc] initWithBytes:"\x0D" length:length]];
        [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x16" length:length] forKey:[[NSData alloc] initWithBytes:"\x10" length:length]];
    } else {
        [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x15" length:length] forKey:[[NSData alloc] initWithBytes:"\x0D" length:length]];
        [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x17" length:length] forKey:[[NSData alloc] initWithBytes:"\x10" length:length]];
    }
    [Dyn1 setObject:[[NSData alloc] initWithBytes:"\x13" length:length] forKey:[[NSData alloc] initWithBytes:"\x0E" length:length]];

    // Distortion
    NSMapTable *Dist1 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x01" length:length] forKey:[[NSData alloc] initWithBytes:"\x0E" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x0B" length:length] forKey:[[NSData alloc] initWithBytes:"\x0D" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x0C" length:length] forKey:[[NSData alloc] initWithBytes:"\x0B" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x0D" length:length] forKey:[[NSData alloc] initWithBytes:"\x16" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x0E" length:length] forKey:[[NSData alloc] initWithBytes:"\x18" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x0F" length:length] forKey:[[NSData alloc] initWithBytes:"\x10" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x10" length:length] forKey:[[NSData alloc] initWithBytes:"\x13" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x11" length:length] forKey:[[NSData alloc] initWithBytes:"\x12" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x18" length:length] forKey:[[NSData alloc] initWithBytes:"\x0F" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x19" length:length] forKey:[[NSData alloc] initWithBytes:"\x0C" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x1A" length:length] forKey:[[NSData alloc] initWithBytes:"\x0A" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x1B" length:length] forKey:[[NSData alloc] initWithBytes:"\x14" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x1D" length:length] forKey:[[NSData alloc] initWithBytes:"\x11" length:length]];
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x1E" length:length] forKey:[[NSData alloc] initWithBytes:"\x17" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x1C" length:length] forKey:[[NSData alloc] initWithBytes:"\x15" length:length]];
    } else {
    [Dist1 setObject:[[NSData alloc] initWithBytes:"\x1A" length:length] forKey:[[NSData alloc] initWithBytes:"\x15" length:length]];
    }

    
    // Modulator
    NSMapTable *Mod1 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Mod1 setObject:[[NSData alloc] initWithBytes:"\x2A" length:length] forKey:[[NSData alloc] initWithBytes:"\x2E" length:length]];
    [Mod1 setObject:[[NSData alloc] initWithBytes:"\x2B" length:length] forKey:[[NSData alloc] initWithBytes:"\x2B" length:length]];
    [Mod1 setObject:[[NSData alloc] initWithBytes:"\x2C" length:length] forKey:[[NSData alloc] initWithBytes:"\x42" length:length]];
    [Mod1 setObject:[[NSData alloc] initWithBytes:"\x2D" length:length] forKey:[[NSData alloc] initWithBytes:"\x26" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [Mod1 setObject:[[NSData alloc] initWithBytes:"\x2E" length:length] forKey:[[NSData alloc] initWithBytes:"\x27" length:length]];
    } else {
        [Mod1 setObject:[[NSData alloc] initWithBytes:"\x2D" length:length] forKey:[[NSData alloc] initWithBytes:"\x27" length:length]];
    }

    
    NSMapTable *Mod2 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x04" length:length] forKey:[[NSData alloc] initWithBytes:"\x2A" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x36" length:length] forKey:[[NSData alloc] initWithBytes:"\x28" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x37" length:length] forKey:[[NSData alloc] initWithBytes:"\x25" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x38" length:length] forKey:[[NSData alloc] initWithBytes:"\x22" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x39" length:length] forKey:[[NSData alloc] initWithBytes:"\x23" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x3A" length:length] forKey:[[NSData alloc] initWithBytes:"\x40" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x3B" length:length] forKey:[[NSData alloc] initWithBytes:"\x24" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x3C" length:length] forKey:[[NSData alloc] initWithBytes:"\x45" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x3D" length:length] forKey:[[NSData alloc] initWithBytes:"\x2D" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x06" length:length] forKey:[[NSData alloc] initWithBytes:"\x20" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x42" length:length] forKey:[[NSData alloc] initWithBytes:"\x21" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x43" length:length] forKey:[[NSData alloc] initWithBytes:"\x43" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x44" length:length] forKey:[[NSData alloc] initWithBytes:"\x2F" length:length]];
    
    // Effect mapped (not available on HD 300)
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x04" length:length] forKey:[[NSData alloc] initWithBytes:"\x2C" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x36" length:length] forKey:[[NSData alloc] initWithBytes:"\x29" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x36" length:length] forKey:[[NSData alloc] initWithBytes:"\x47" length:length]];
    [Mod2 setObject:[[NSData alloc] initWithBytes:"\x36" length:length] forKey:[[NSData alloc] initWithBytes:"\x49" length:length]];
    
    NSMapTable *Filter1 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Filter1 setObject:[[NSData alloc] initWithBytes:"\x27" length:length] forKey:[[NSData alloc] initWithBytes:"\x10" length:length]];
    [Filter1 setObject:[[NSData alloc] initWithBytes:"\x28" length:length] forKey:[[NSData alloc] initWithBytes:"\x0F" length:length]];
    [Filter1 setObject:[[NSData alloc] initWithBytes:"\x29" length:length] forKey:[[NSData alloc] initWithBytes:"\x14" length:length]];
    [Filter1 setObject:[[NSData alloc] initWithBytes:"\x31" length:length] forKey:[[NSData alloc] initWithBytes:"\x1C" length:length]];
    [Filter1 setObject:[[NSData alloc] initWithBytes:"\x32" length:length] forKey:[[NSData alloc] initWithBytes:"\x19" length:length]];
    [Filter1 setObject:[[NSData alloc] initWithBytes:"\x33" length:length] forKey:[[NSData alloc] initWithBytes:"\x1A" length:length]];
    [Filter1 setObject:[[NSData alloc] initWithBytes:"\x35" length:length] forKey:[[NSData alloc] initWithBytes:"\x1E" length:length]];    
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [Filter1 setObject:[[NSData alloc] initWithBytes:"\x30" length:length] forKey:[[NSData alloc] initWithBytes:"\x1B" length:length]];
    } else {
        [Filter1 setObject:[[NSData alloc] initWithBytes:"\x31" length:length] forKey:[[NSData alloc] initWithBytes:"\x1B" length:length]];
    }
    
    NSMapTable *Filter2 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Filter2 setObject:[[NSData alloc] initWithBytes:"\x05" length:length] forKey:[[NSData alloc] initWithBytes:"\x11" length:length]];
    [Filter2 setObject:[[NSData alloc] initWithBytes:"\x3E" length:length] forKey:[[NSData alloc] initWithBytes:"\x15" length:length]];
    [Filter2 setObject:[[NSData alloc] initWithBytes:"\x3F" length:length] forKey:[[NSData alloc] initWithBytes:"\x16" length:length]];
    [Filter2 setObject:[[NSData alloc] initWithBytes:"\x40" length:length] forKey:[[NSData alloc] initWithBytes:"\x14" length:length]];
    [Filter2 setObject:[[NSData alloc] initWithBytes:"\x41" length:length] forKey:[[NSData alloc] initWithBytes:"\x1D" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [Filter2 setObject:[[NSData alloc] initWithBytes:"\x26" length:length] forKey:[[NSData alloc] initWithBytes:"\x13" length:length]];
        [Filter2 setObject:[[NSData alloc] initWithBytes:"\x5D" length:length] forKey:[[NSData alloc] initWithBytes:"\x18" length:length]];
    } else {
        [Filter2 setObject:[[NSData alloc] initWithBytes:"\x3E" length:length] forKey:[[NSData alloc] initWithBytes:"\x13" length:length]];
        [Filter2 setObject:[[NSData alloc] initWithBytes:"\x3F" length:length] forKey:[[NSData alloc] initWithBytes:"\x18" length:length]];
    }
    [Filter2 setObject:[[NSData alloc] initWithBytes:"\x05" length:length] forKey:[[NSData alloc] initWithBytes:"\x26" length:length]];
    [Filter2 setObject:[[NSData alloc] initWithBytes:"\x3F" length:length] forKey:[[NSData alloc] initWithBytes:"\x17" length:length]];
    
    // Pitcher
    NSMapTable *Pitch1 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Pitch1 setObject:[[NSData alloc] initWithBytes:"\x03" length:length] forKey:[[NSData alloc] initWithBytes:"\x03" length:length]];
    [Pitch1 setObject:[[NSData alloc] initWithBytes:"\x2F" length:length] forKey:[[NSData alloc] initWithBytes:"\x02" length:length]];
    [Pitch1 setObject:[[NSData alloc] initWithBytes:"\x34" length:length] forKey:[[NSData alloc] initWithBytes:"\x04" length:length]];

    // Equalizer
    NSMapTable *Eq1 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Eq1 setObject:[[NSData alloc] initWithBytes:"\x23" length:length] forKey:[[NSData alloc] initWithBytes:"\x0B" length:length]];
    [Eq1 setObject:[[NSData alloc] initWithBytes:"\x24" length:length] forKey:[[NSData alloc] initWithBytes:"\x0C" length:length]];
    [Eq1 setObject:[[NSData alloc] initWithBytes:"\x5E" length:length] forKey:[[NSData alloc] initWithBytes:"\x0E" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [Eq1 setObject:[[NSData alloc] initWithBytes:"\x21" length:length] forKey:[[NSData alloc] initWithBytes:"\x09" length:length]];
        [Eq1 setObject:[[NSData alloc] initWithBytes:"\x22" length:length] forKey:[[NSData alloc] initWithBytes:"\x0A" length:length]];
        [Eq1 setObject:[[NSData alloc] initWithBytes:"\x25" length:length] forKey:[[NSData alloc] initWithBytes:"\x0D" length:length]];
    } else {
        [Eq1 setObject:[[NSData alloc] initWithBytes:"\x23" length:length] forKey:[[NSData alloc] initWithBytes:"\x09" length:length]];
        [Eq1 setObject:[[NSData alloc] initWithBytes:"\x24" length:length] forKey:[[NSData alloc] initWithBytes:"\x0A" length:length]];
        [Eq1 setObject:[[NSData alloc] initWithBytes:"\x24" length:length] forKey:[[NSData alloc] initWithBytes:"\x0D" length:length]];
    }
    
    // Delay
    NSMapTable *Delay3 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x07" length:length] forKey:[[NSData alloc] initWithBytes:"\x11" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x45" length:length] forKey:[[NSData alloc] initWithBytes:"\x12" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x46" length:length] forKey:[[NSData alloc] initWithBytes:"\x14" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x47" length:length] forKey:[[NSData alloc] initWithBytes:"\x15" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x48" length:length] forKey:[[NSData alloc] initWithBytes:"\x30" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x49" length:length] forKey:[[NSData alloc] initWithBytes:"\x31" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x4A" length:length] forKey:[[NSData alloc] initWithBytes:"\x1D" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x4B" length:length] forKey:[[NSData alloc] initWithBytes:"\x13" length:length]];
    
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x4C" length:length] forKey:[[NSData alloc] initWithBytes:"\x20" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x4D" length:length] forKey:[[NSData alloc] initWithBytes:"\x22" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x08" length:length] forKey:[[NSData alloc] initWithBytes:"\x2C" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x4E" length:length] forKey:[[NSData alloc] initWithBytes:"\x2D" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x4F" length:length] forKey:[[NSData alloc] initWithBytes:"\x2A" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x50" length:length] forKey:[[NSData alloc] initWithBytes:"\x2B" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x09" length:length] forKey:[[NSData alloc] initWithBytes:"\x23" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x52" length:length] forKey:[[NSData alloc] initWithBytes:"\x2E" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x53" length:length] forKey:[[NSData alloc] initWithBytes:"\x2F" length:length]];
    [Delay3 setObject:[[NSData alloc] initWithBytes:"\x54" length:length] forKey:[[NSData alloc] initWithBytes:"\x21" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [Delay3 setObject:[[NSData alloc] initWithBytes:"\x51" length:length] forKey:[[NSData alloc] initWithBytes:"\x1A" length:length]];
    } else {
        [Delay3 setObject:[[NSData alloc] initWithBytes:"\x07" length:length] forKey:[[NSData alloc] initWithBytes:"\x1A" length:length]];
    }
    
    // Reverb
    NSMapTable *Reverb1 = [NSMapTable mapTableWithStrongToStrongObjects];
    [Reverb1 setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x1D" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [Reverb1 setObject:[[NSData alloc] initWithBytes:"\x1F" length:length] forKey:[[NSData alloc] initWithBytes:"\x1C" length:length]];
        [Reverb1 setObject:[[NSData alloc] initWithBytes:"\x20" length:length] forKey:[[NSData alloc] initWithBytes:"\x27" length:length]];
    } else {
        [Reverb1 setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x1C" length:length]];
        [Reverb1 setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x27" length:length]];
    }
    
    NSMapTable *ReverbSlot = [NSMapTable mapTableWithStrongToStrongObjects];
    [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x0A" length:length] forKey:[[NSData alloc] initWithBytes:"\x1E" length:length]];
    [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x55" length:length] forKey:[[NSData alloc] initWithBytes:"\x1F" length:length]];
    [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x56" length:length] forKey:[[NSData alloc] initWithBytes:"\x20" length:length]];
    [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x57" length:length] forKey:[[NSData alloc] initWithBytes:"\x21" length:length]];
    [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x58" length:length] forKey:[[NSData alloc] initWithBytes:"\x24" length:length]];
    [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x5A" length:length] forKey:[[NSData alloc] initWithBytes:"\x23" length:length]];
    [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x5B" length:length] forKey:[[NSData alloc] initWithBytes:"\x25" length:length]];
    [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x5C" length:length] forKey:[[NSData alloc] initWithBytes:"\x26" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x29" length:length] forKey:[[NSData alloc] initWithBytes:"\x22" length:length]];
    } else {
        [ReverbSlot setObject:[[NSData alloc] initWithBytes:"\x58" length:length] forKey:[[NSData alloc] initWithBytes:"\x22" length:length]];
    }

    NSMapTable *WahSlot = [NSMapTable mapTableWithStrongToStrongObjects];
    [WahSlot setObject:[[NSData alloc] initWithBytes:"\x00" length:length] forKey:[[NSData alloc] initWithBytes:"\x0B" length:length]];
    [WahSlot setObject:[[NSData alloc] initWithBytes:"\x01" length:length] forKey:[[NSData alloc] initWithBytes:"\x0C" length:length]];
    [WahSlot setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x0E" length:length]];
    [WahSlot setObject:[[NSData alloc] initWithBytes:"\x03" length:length] forKey:[[NSData alloc] initWithBytes:"\x0D" length:length]];
    [WahSlot setObject:[[NSData alloc] initWithBytes:"\x04" length:length] forKey:[[NSData alloc] initWithBytes:"\x11" length:length]];
    [WahSlot setObject:[[NSData alloc] initWithBytes:"\x05" length:length] forKey:[[NSData alloc] initWithBytes:"\x12" length:length]];
    
    // Effect mapped (not available on HD 300)
    if ([chkbxPatchH4e state] == NSOnState) {
        [WahSlot setObject:[[NSData alloc] initWithBytes:"\x06" length:length] forKey:[[NSData alloc] initWithBytes:"\x10" length:length]];
        [WahSlot setObject:[[NSData alloc] initWithBytes:"\x07" length:length] forKey:[[NSData alloc] initWithBytes:"\x0F" length:length]];
    } else {
        [WahSlot setObject:[[NSData alloc] initWithBytes:"\x04" length:length] forKey:[[NSData alloc] initWithBytes:"\x10" length:length]];
        [WahSlot setObject:[[NSData alloc] initWithBytes:"\x02" length:length] forKey:[[NSData alloc] initWithBytes:"\x0F" length:length]];
    }
    
    @autoreleasepool {
        
        for (int i = 0; i < [presetFiles count] ; i = i+1) {
            
            // SourceFile
            NSString *presetSourceName = [presetFiles objectAtIndex:i];
            NSString *pathToSourcePreset = [[path path] stringByAppendingPathComponent:presetSourceName];
                    
            // TargetFile
            NSString *presetNameNoExtension = [[presetFiles objectAtIndex:i] stringByDeletingPathExtension];
            NSString *pathToTargetPreset = [[[path path] stringByAppendingPathComponent:presetNameNoExtension] stringByAppendingPathExtension:toExtension];
            
            // Create Target File
            [[NSFileManager defaultManager] createFileAtPath:pathToTargetPreset contents:h3eStructure attributes:nil];

            // Open Files
            NSFileHandle *sourceFile = [NSFileHandle fileHandleForReadingAtPath: pathToSourcePreset];
            NSFileHandle *targetFile = [NSFileHandle fileHandleForUpdatingAtPath: pathToTargetPreset];

            if (sourceFile == nil)
                NSLog(@"Failed to open preset");
            
            if (targetFile == nil)
                NSLog(@"Failed to create new preset");
            
            // Read data for testing purpose
            //databuffer = [modifyFile readDataOfLength: 1];
            //NSLog (@"Data = %@", databuffer);
            
            // Set Preset Name
            [sourceFile seekToFileOffset: 0x28];
            databuffer = [sourceFile readDataOfLength: 16];
            [targetFile seekToFileOffset: 0x28];
            [targetFile writeData: databuffer];
            
            // Check if first Amp is On
            [sourceFile seekToFileOffset: 0x58];
            databuffer = [sourceFile readDataOfLength: 1];
            if ([databuffer isEqual:[NSData dataWithBytes: "\x01" length: length]]) {
                ampOn = true;
            }
            
            // Seek and Write first Amp Model
            
            [sourceFile seekToFileOffset: 0x53];
            databuffer = [sourceFile readDataOfLength: 1];
            [targetFile seekToFileOffset: 0x3B];
            [targetFile writeData: [Amps objectForKey:databuffer]];
            
            // Check for PreAmp
            
            [sourceFile seekToFileOffset: 0x53];
            databuffer = [sourceFile readDataOfLength: 1];
            if ([PreAmps objectForKey:databuffer]) {
                [targetFile seekToFileOffset: 0x4D];
                [targetFile writeData:[NSData dataWithBytes: "\x01" length: length]];
            } else {
                [targetFile seekToFileOffset: 0x4D];
                [targetFile writeData:[NSData dataWithBytes: "\x00" length: length]];
            }
            
            // Turn first Cab On
            
            [sourceFile seekToFileOffset: 0x25B];
            databuffer = [sourceFile readDataOfLength: 1];
            if ([databuffer isEqual:[NSData dataWithBytes: "\x00" length: length]]) {
                [targetFile seekToFileOffset: 0x3D];
                [targetFile writeData:[NSData dataWithBytes: "\x12" length: length]];
            }
            
            // Seek and Write for first Cab Model
            
            [sourceFile seekToFileOffset: 0x253];
            databuffer = [sourceFile readDataOfLength: 1];
            [targetFile seekToFileOffset: 0x3D];
            [targetFile writeData: [Cabs objectForKey:databuffer]];
            
            // Convert (From 4 Bytes (float) to 2 Bytes (int)) Amp Potis and write them down
            // Drive
            [self poti:sourceFile targetfile:targetFile sourcePosition:0x64 targetPosition:0x3E];
            
            // Bass
            [self poti:sourceFile targetfile:targetFile sourcePosition:0x78 targetPosition:0x40];
            
            // Mid
            [self poti:sourceFile targetfile:targetFile sourcePosition:0x8C targetPosition:0x42];
            
            // Treble
            [self poti:sourceFile targetfile:targetFile sourcePosition:0xA0 targetPosition:0x44];
            
            // Pres
            [self poti:sourceFile targetfile:targetFile sourcePosition:0xB4 targetPosition:0x48];
            
            // CH. Vol
            [self poti:sourceFile targetfile:targetFile sourcePosition:0xC8 targetPosition:0x46];
            
            // E.R.
            [self poti:sourceFile targetfile:targetFile sourcePosition:0xD74 targetPosition:0x4E];
            
            
            
            // BYP Vol.
            [self poti:sourceFile targetfile:targetFile sourcePosition:0xDA4 targetPosition:0x50];
            
            
            
            // Master
            [self poti:sourceFile targetfile:targetFile sourcePosition:0x12C targetPosition:0x64];
            
            // Sag
            [self poti:sourceFile targetfile:targetFile sourcePosition:0xF0 targetPosition:0x5E];
            
            // Hum
            [self poti:sourceFile targetfile:targetFile sourcePosition:0xDC targetPosition:0x5C];
            
            // Bias
            [self poti:sourceFile targetfile:targetFile sourcePosition:0x104 targetPosition:0x60];
            
            // Bias X
            [self poti:sourceFile targetfile:targetFile sourcePosition:0x118 targetPosition:0x62];
            
            // Cab Parameter (Not Available on POD HD 300?)
            
            // Low Cut
            //[self poti:sourceFile targetfile:targetFile sourcePosition:0x264 targetPosition:0x];
            
            // Res Level
            //[self poti:sourceFile targetfile:targetFile sourcePosition:0x278 targetPosition:0x];
            
            // Thump
            //[self poti:sourceFile targetfile:targetFile sourcePosition:0x28C targetPosition:0x];
            
            // Decay
            //[self poti:sourceFile targetfile:targetFile sourcePosition:0x2A0 targetPosition:0x];
            
            // Microphone
            
            [sourceFile seekToFileOffset: 0x1020];
            databuffer = [sourceFile readDataOfLength: 1];
            [targetFile seekToFileOffset: 0x4C];
            [targetFile writeData: databuffer];
            
            // Effects
            
            // Check which effects are available
            
            NSData *effectTypeNSData, *effectModellNSData;
            
            // holds Number of Effects in Slots (HD 300)
            int fx1 = 0, fx2 = 0, fx3 = 0, reverbSlot = 0, Wah = 0;
                        
            // Check for Number of Effects in Slots
            
            for (int j = 0x0; j<0x800; j += 0x100) {
                
                [sourceFile seekToFileOffset: (0x451 + j)];
                effectTypeNSData = [sourceFile readDataOfLength: length];
                
                const char *incomingPacket = (const char *) [effectTypeNSData bytes];
                char effectType = incomingPacket[0];
                
                switch (effectType) {
                    case 0x00:
                        // Dyn Effect
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        
                        if ([Dyn1 objectForKey:effectModellNSData]) {
                            fx1 += 1;
                        }
                        break;
                    case 0x05:
                        // Dist Effect
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        
                        if ([Dist1 objectForKey:effectModellNSData]) {
                            
                            fx1 += 1;
                        }
                        break;
                    case 0x03:
                        // Mod Effect
                        
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        if ([Mod1 objectForKey:effectModellNSData]) {
                            
                            fx1 += 1;
                            
                            // Check for 2nd Slot
                            
                            // Check for Type of Effect
                        } else if ([Mod2 objectForKey:effectModellNSData]) {
                            
                            fx2 += 1;
                        }
                        break;
                    case 0x0A:
                        // Filter Effect
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        if ([Filter1 objectForKey:effectModellNSData]) {
                            
                            fx1 += 1;
                            
                            // Check for 2nd Slot
                            
                            // Check for Type of Effect
                        } else if ([Filter2 objectForKey:effectModellNSData]) {
                            
                            fx2 += 1;
                        }
                        break;
                    case 0x09:
                        // Pitch Effect
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        if ([Pitch1 objectForKey:effectModellNSData]) {
                            
                            
                            fx1 += 1;
                        }
                        break;
                    case 0x0C:
                        //  EQ+Pre Effect
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        if ([Eq1 objectForKey:effectModellNSData]) {
                            
                            fx1 += 1;
                        }
                        break;
                    case 0x02:
                        // Delay Effect
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        if ([Delay3 objectForKey:effectModellNSData]) {
                            
                            fx3 += 1;
                        }
                        break;
                    case 0x04:
                        // Reverb Effect
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        if ([Reverb1 objectForKey:effectModellNSData]) {
                            
                            fx1 += 1;
                            
                            // Check for ReverbSlot
                            
                            // Check for Type of Effect
                        } else if ([ReverbSlot objectForKey:effectModellNSData]) {
                            
                            reverbSlot += 1;
                        }
                        break;
                    case 0x07:
                        //  VolPan Effect
                        break;
                    case 0x06:
                        // Wah Effect
                        
                        // Check for Type of Effect
                        [sourceFile seekToFileOffset: (0x453 + j)];
                        effectModellNSData = [sourceFile readDataOfLength: 1];
                        if ([WahSlot objectForKey:effectModellNSData]) {
                            
                            Wah += 1;
                        }
                        break;
                    case 0x08:
                        // FXLoop Effect
                        break;
                }
            }
            
            [targetFile closeFile];
            
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
                                
                                // TargetFileLoopName
                                //NSString *presetNameNoExtension = [[presetFiles objectAtIndex:i] stringByDeletingPathExtension];
                                NSString *pathToTargetPresetLoopName = [[[[[[[[path path] stringByAppendingPathComponent:presetNameNoExtension] stringByAppendingString: [NSString stringWithFormat:@"%d", v]] stringByAppendingString: [NSString stringWithFormat:@"%d", w]] stringByAppendingString: [NSString stringWithFormat:@"%d", x]] stringByAppendingString: [NSString stringWithFormat:@"%d", y]] stringByAppendingString: [NSString stringWithFormat:@"%d", z]] stringByAppendingPathExtension: toExtension];
                                
                                // Copy Template to Files
                                
                                NSFileManager *filemgr = [NSFileManager defaultManager];
                                
                                NSError *err;
                                
                                //NSLog(@"%@", pathToTargetPreset);
                                //NSLog(@"%@", pathToTargetPresetLoopName);
                                
                                BOOL success = [filemgr copyItemAtPath: pathToTargetPreset toPath: pathToTargetPresetLoopName error: &err];
                                
                                if (!success) {
                                    @throw [NSException exceptionWithName:[err localizedDescription] reason:[err localizedFailureReason] userInfo:nil];
                                }
                                
                                // Open File
                                NSFileHandle *targetFileLoop = [NSFileHandle fileHandleForUpdatingAtPath: pathToTargetPresetLoopName];
                                
                                if (targetFileLoop == nil)
                                    NSLog(@"Failed to open loop preset");
                                
                                int fx1a = 1, fx2a = 1, fx3a = 1, reverbSlota = 1, Waha = 1;
                                
                                NSData *effectPrePost, *effectOn, *effectModellNSData;
                                
                                NSSet *preEffects = [NSSet setWithObjects:[[NSData alloc] initWithBytes:"\x00" length:length], [[NSData alloc] initWithBytes:"\x01" length:length], [[NSData alloc] initWithBytes:"\x02" length:length],nil];
                                NSSet *postEffects = [NSSet setWithObjects:[[NSData alloc] initWithBytes:"\x03" length:length], [[NSData alloc] initWithBytes:"\x04" length:length], [[NSData alloc] initWithBytes:"\x05" length:length],nil];
                                
                                for (int j = 0x0; j<0x800; j += 0x100) {
                                    
                                    [sourceFile seekToFileOffset: (0x451 + j)];
                                    effectTypeNSData = [sourceFile readDataOfLength: length];
                                    
                                    const char *incomingPacket = (const char *) [effectTypeNSData bytes];
                                    char effectType = incomingPacket[0];
                                    
                                    switch (effectType) {
                                        case 0x00:
                                            // Dyn Effect
                                            
                                            // Check for Type of Effect
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            
                                            // Check for Noise Gate
                                            
                                            if ([effectModellNSData isEqual:[NSData dataWithBytes: "\x11" length: length]]) {
                                                // Found NoiseGate
                                                
                                                // 1. Poti - Tresh
                                                [self potiDecibel:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x58];
                                                
                                                // 2. Poti - Decay
                                                [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x5A];
                                                
                                                hasNoiseGate = true;
                                            }
                                            
                                            // Set Effect
                                            if ([Dyn1 objectForKey:effectModellNSData]) {
                                                if (fx1a == v) {
                                                   [targetFileLoop seekToFileOffset: (0x75)];
                                                    [targetFileLoop writeData: [Dyn1 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6E)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x8C];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x8E];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x90];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x92];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0x94];

                                                }
                                                fx1a += 1;

                                            }
                                            break;
                                        case 0x05:
                                            // Dist Effect

                                            // Check for Type of Effect
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            if ([Dist1 objectForKey:effectModellNSData]) {
                                                if (fx1a == v) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    [targetFileLoop writeData: [Dist1 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6E)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x8C];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x8E];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x90];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x92];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0x94];

                                                }
                                                fx1a++;

                                            }
                                            break;
                                        case 0x03:
                                            // Mod Effect


                                            // Check for Type of Effect
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            if ([Mod1 objectForKey:effectModellNSData]) {
                                                if (fx1a == v) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    [targetFileLoop writeData: [Mod1 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6E)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x8C];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x8E];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x90];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x92];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0x94];

                                                }
                                                fx1a += 1;

                                            // Check for 2nd Slot


                                            // Check for Type of Effect
                                            } else if ([Mod2 objectForKey:effectModellNSData]) {
                                                if (fx2a == w) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x7D)];
                                                    [targetFileLoop writeData: [Mod2 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x7D)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6F)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x7A)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x7A)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x7A)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x7A)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x96];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x98];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x9A];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x9C];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0xA0];

                                                }
                                                fx2a += 1;

                                            }
                                            break;
                                        case 0x0A:
                                            // Filter Effect

                                            // Check for Type of Effect
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            if ([Filter1 objectForKey:effectModellNSData]) {
                                                if (fx1a == v) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    [targetFileLoop writeData: [Filter1 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6E)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x8C];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x8E];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x90];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x92];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0x94];

                                                }
                                                fx1a += 1;

                                            // Check for 2nd Slot

                                            // Check for Type of Effect
                                            } else if ([Filter2 objectForKey:effectModellNSData]) {
                                                if (fx2a == w) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x7D)];
                                                    [targetFileLoop writeData: [Filter2 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x7D)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6F)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x7A)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x7A)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x7A)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x7A)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x96];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x98];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x9A];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x9C];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0xA0];

                                                }
                                                fx2a += 1;

                                            }
                                            break;
                                        case 0x09:
                                            // Pitch Effect

                                            // Check for Type of Effect
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            if ([Pitch1 objectForKey:effectModellNSData]) {
                                                if (fx1a == v) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    [targetFileLoop writeData: [Pitch1 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6E)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x8C];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x8E];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x90];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x92];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0x94];

                                                }
                                                fx1a += 1;

                                            }
                                            break;
                                        case 0x0C:
                                            //  EQ+Pre Effect

                                            // Check for Type of Effect
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            if ([Eq1 objectForKey:effectModellNSData]) {
                                                if (fx1a == v) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    [targetFileLoop writeData: [Eq1 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6E)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x8C];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x8E];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x90];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x92];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0x94];

                                                }
                                                fx1a += 1;

                                            }
                                            break;
                                        case 0x02:
                                            // Delay Effect

                                            // Check for Type of Effect
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            if ([Delay3 objectForKey:effectModellNSData]) {
                                                if (fx3a == x) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x85)];
                                                    [targetFileLoop writeData: [Delay3 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x85)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x70)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x82)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x82)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x82)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x82)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0xA2];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0xA4];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0xA6];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0xA8];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0xAA];

                                                }
                                                fx3a += 1;

                                            }
                                            break;
                                        case 0x04:
                                            // Reverb Effect

                                            // Check for Type of Effect
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            if ([Reverb1 objectForKey:effectModellNSData]) {
                                                if (fx1a == v) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    [targetFileLoop writeData: [Reverb1 objectForKey:effectModellNSData]];

                                                    // Write again at different Place
                                                    [targetFileLoop seekToFileOffset: (0x75)];
                                                    databuffer = [targetFileLoop readDataOfLength: 1];
                                                    [targetFileLoop seekToFileOffset: (0x6E)];
                                                    [targetFileLoop writeData: databuffer];

                                                    // See if Effect is Online and Set it On
                                                    [sourceFile seekToFileOffset: (0x45B + j)];
                                                    effectOn = [sourceFile readDataOfLength: 1];
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x01" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOnPost];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [preEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPre];
                                                    } else if ([effectOn isEqual:[NSData dataWithBytes: "\x00" length: length]] && [postEffects containsObject: effectPrePost]) {
                                                        [targetFileLoop seekToFileOffset: (0x72)];
                                                        [targetFileLoop writeData: fxOffPost];
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0x8C];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0x8E];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0x90];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0x92];

                                                    // 5. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4B4 + j) targetPosition:0x94];

                                                }
                                                fx1a += 1;

                                            // Check for ReverbSlot

                                            // Check for Type of Effect
                                            } else if ([ReverbSlot objectForKey:effectModellNSData]) {
                                                if (reverbSlota == y) {
                                                    
                                                    [targetFileLoop seekToFileOffset: (0x6C)];
                                                    [targetFileLoop writeData: [ReverbSlot objectForKey:effectModellNSData]];

                                                    // Set Pre/Post since it is always on
                                                    [sourceFile seekToFileOffset: (0x455 + j)];
                                                    effectPrePost = [sourceFile readDataOfLength: 1];
                                                    if ([preEffects containsObject: effectPrePost]) {
                                                        reverbPrePost = false; // Set false if Pre
                                                    } else if ([postEffects containsObject: effectPrePost]) {
                                                        reverbPrePost = true; // Set true if Post
                                                    }

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0xB0];

                                                    // 2. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x478 + j) targetPosition:0xB2];

                                                    // 3. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x48C + j) targetPosition:0xB4];

                                                    // 4. Poti
                                                    [self poti:sourceFile targetfile:targetFileLoop sourcePosition:(0x4A0 + j) targetPosition:0xB8];

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
                                            [sourceFile seekToFileOffset: (0x453 + j)];
                                            effectModellNSData = [sourceFile readDataOfLength: 1];
                                            if ([WahSlot objectForKey:effectModellNSData]) {
                                                if (Waha == z) {
                                                    [targetFileLoop seekToFileOffset: (0x6D)];
                                                    [targetFileLoop writeData: [WahSlot objectForKey:effectModellNSData]];

                                                    // Set Potis

                                                    // 1. Poti
                                                    [self potiByte:sourceFile targetfile:targetFileLoop sourcePosition:(0x464 + j) targetPosition:0xBA];

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
                                
                                [targetFileLoop seekToFileOffset: (0x39)];
                                if (ampOn && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x80" length: length]];
                                } else if (ampOn && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x88" length: length]];
                                } else if (ampOn && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x81" length: length]];
                                } else if (ampOn && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x89" length: length]];
                                } else if (ampOn && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\xC0" length: length]];
                                } else if (ampOn && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\xC8" length: length]];
                                } else if (ampOn && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\xC1" length: length]];
                                } else if (ampOn && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\xC9" length: length]];
                                    
                                } else if (ampOn == false && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x00" length: length]];
                                } else if (ampOn == false && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x08" length: length]];
                                } else if (ampOn == false && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x01" length: length]];
                                } else if (ampOn == false && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x09" length: length]];
                                } else if (ampOn == false && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x40" length: length]];
                                } else if (ampOn == false && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x48" length: length]];
                                } else if (ampOn == false && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x41" length: length]];
                                } else if (ampOn == false && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
                                    [targetFileLoop writeData:[NSData dataWithBytes: "\x49" length: length]];
                                }
                                
                                [targetFileLoop closeFile];
                                
                                // Check for Dualamp Preset and MultiSlot Assignment
                                
                                // Check if 2nd Amp set (either off or on, but defined)
                                [sourceFile seekToFileOffset: (0x15B)];
                                databuffer = [sourceFile readDataOfLength: length];
                                    if ([databuffer isEqual:[NSData dataWithBytes: "\x01" length: length]]) {
                                    
                                    // Found 2nd Amp, do something!
                                    hasDualamp = true;
                                    
                                }
                                
                                if (hasDualamp) {
                                    
                                    // Define FileNames
                                    
                                    // TargetFileLoopName2ndAmp
                                    //NSString *presetNameNoExtension = [[presetFiles objectAtIndex:i] stringByDeletingPathExtension];
            
                                    NSString *pathToTargetPresetLoopName2ndAmp = [[[pathToTargetPresetLoopName stringByDeletingPathExtension] stringByAppendingString: [NSString stringWithFormat:@"2ndAmp"]] stringByAppendingPathExtension: toExtension];
                                    
                                    // Copy Template to Files
                                    
                                    NSFileManager *filemgr = [NSFileManager defaultManager];
                                    
                                    NSError *err;
                                    
                                    //NSLog(@"%@", pathToTargetPresetLoopName);
                                    //NSLog(@"%@", pathToTargetPresetLoopName2ndAmp);
                                    
                                    BOOL success = [filemgr copyItemAtPath: pathToTargetPresetLoopName toPath: pathToTargetPresetLoopName2ndAmp error: &err];
                                    
                                    if (!success) {
                                        @throw [NSException exceptionWithName:[err localizedDescription] reason:[err localizedFailureReason] userInfo:nil];
                                    }
                                    
                                    // Open File
                                    NSFileHandle *targetFileLoop2ndAmp = [NSFileHandle fileHandleForUpdatingAtPath: pathToTargetPresetLoopName2ndAmp];
                                    
                                    if (targetFileLoop2ndAmp == nil)
                                        NSLog(@"Failed to open 2ndAmp preset");
                                    
                                    // Check if second Amp is On
                                    [sourceFile seekToFileOffset: 0x158];
                                    databuffer = [sourceFile readDataOfLength: 1];
                                    if ([databuffer isEqual:[NSData dataWithBytes: "\x01" length: length]]) {
                                        amp2On = true;
                                    }
                                    
                                    // Seek and Write first Amp Model
                                    
                                    [sourceFile seekToFileOffset: 0x153];
                                    databuffer = [sourceFile readDataOfLength: 1];
                                    [targetFileLoop2ndAmp seekToFileOffset: 0x3B];
                                    [targetFileLoop2ndAmp writeData: [Amps objectForKey:databuffer]];
                                    
                                    // Check for PreAmp
                                    
                                    [sourceFile seekToFileOffset: 0x153];
                                    databuffer = [sourceFile readDataOfLength: 1];
                                    if ([PreAmps objectForKey:databuffer]) {
                                        [targetFileLoop2ndAmp seekToFileOffset: 0x4D];
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x01" length: length]];
                                    } else {
                                        [targetFileLoop2ndAmp seekToFileOffset: 0x4D];
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x00" length: length]];
                                    }
                                    
                                    // Turn second Cab On
                                    
                                    [sourceFile seekToFileOffset: 0x35B];
                                    databuffer = [sourceFile readDataOfLength: 1];
                                    if ([databuffer isEqual:[NSData dataWithBytes: "\x00" length: length]]) {
                                        [targetFileLoop2ndAmp seekToFileOffset: 0x3D];
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x12" length: length]];
                                    }
                                    
                                    // Seek and Write for first Cab Model
                                    
                                    [sourceFile seekToFileOffset: 0x353];
                                    databuffer = [sourceFile readDataOfLength: 1];
                                    [targetFileLoop2ndAmp seekToFileOffset: 0x3D];
                                    [targetFileLoop2ndAmp writeData: [Cabs objectForKey:databuffer]];
                                    
                                    // Convert (From 4 Bytes (float) to 2 Bytes (int)) Amp Potis and write them down
                                    // Drive
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x164 targetPosition:0x3E];
                                    
                                    // Bass
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x178 targetPosition:0x40];
                                    
                                    // Mid
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x18C targetPosition:0x42];
                                    
                                    // Treble
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x1A0 targetPosition:0x44];
                                    
                                    // Pres
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x1B4 targetPosition:0x48];
                                    
                                    // CH. Vol
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x1C8 targetPosition:0x46];
                                    
                                    // E.R.
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0xD7C targetPosition:0x4E];
                                    
                                    
                                    
                                    // BYP Vol.
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0xDA8 targetPosition:0x50];
                                    
                                    
                                    
                                    // Master
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x22C targetPosition:0x64];
                                    
                                    // Sag
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x2F0 targetPosition:0x5E];
                                    
                                    // Hum
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x2DC targetPosition:0x5C];
                                    
                                    // Bias
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x204 targetPosition:0x60];
                                    
                                    // Bias X
                                    [self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x218 targetPosition:0x62];
                                    
                                    // Cab Parameter (Not Available on POD HD 300?)
                                    
                                    // Low Cut
                                    //[self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x364 targetPosition:0x];
                                    
                                    // Res Level
                                    //[self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x378 targetPosition:0x];
                                    
                                    // Thump
                                    //[self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x38C targetPosition:0x];
                                    
                                    // Decay
                                    //[self poti:sourceFile targetfile:targetFileLoop2ndAmp sourcePosition:0x3A0 targetPosition:0x];
                                    
                                    // Microphone
                                    
                                    [sourceFile seekToFileOffset: 0x1021];
                                    databuffer = [sourceFile readDataOfLength: 1];
                                    [targetFileLoop2ndAmp seekToFileOffset: 0x4C];
                                    [targetFileLoop2ndAmp writeData: databuffer];
                                    
                                    
                                    
                                    // Setup Amp, NoiseGate, Wah and Reverb Byte:
                                    
                                    [targetFileLoop2ndAmp seekToFileOffset: (0x39)];
                                    if (amp2On && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x80" length: length]];
                                    } else if (amp2On && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x88" length: length]];
                                    } else if (amp2On && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x81" length: length]];
                                    } else if (amp2On && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x89" length: length]];
                                    } else if (amp2On && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\xC0" length: length]];
                                    } else if (amp2On && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\xC8" length: length]];
                                    } else if (amp2On && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\xC1" length: length]];
                                    } else if (amp2On && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\xC9" length: length]];
                                        
                                    } else if (amp2On == false && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x00" length: length]];
                                    } else if (amp2On == false && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x08" length: length]];
                                    } else if (amp2On == false && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x01" length: length]];
                                    } else if (amp2On == false && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x09" length: length]];
                                    } else if (amp2On == false && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x40" length: length]];
                                    } else if (amp2On == false && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x48" length: length]];
                                    } else if (amp2On == false && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x41" length: length]];
                                    } else if (amp2On == false && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
                                        [targetFileLoop2ndAmp writeData:[NSData dataWithBytes: "\x49" length: length]];
                                    }
                                    
                                    [targetFileLoop2ndAmp closeFile];
                                    
                                }
                            }
                        }
                    }
                }
            }
                                
            [sourceFile closeFile];
                
            NSFileManager *filemgr = [NSFileManager defaultManager];
            NSError *err;

            BOOL success = [filemgr removeItemAtPath:pathToTargetPreset error:&err ];
            
            if (!success) { 
                @throw [NSException exceptionWithName:[err localizedDescription] reason:[err localizedFailureReason] userInfo:nil];
            }
                
        }
    }
    [pool release];        
} 

- (void) modifyBundleFiles: (NSArray *) presetFiles fromPath:(NSURL *)path {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    @autoreleasepool {
        
        for (int i = 0; i < [presetFiles count] ; i = i+1) {
            
            NSString *pathToPreset;
            
            NSString *presetName = [presetFiles objectAtIndex:i];
            pathToPreset = [[path path] stringByAppendingPathComponent:presetName];
                        
            //NSLog(@"File to be modified: %@", fullPathPreset);
            
            // Header
                        
            NSData *data00000B = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data00000D = [[NSData alloc] initWithBytes:"\x01" length:length]; 
            NSData *data000017 = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data000033 = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data000035 = [[NSData alloc] initWithBytes:"\x01" length:length];
            NSData *data00003F = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data00006B = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data000073 = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data000075 = [[NSData alloc] initWithBytes:"\x01" length:length];

            // Content
             
            NSData *data001093 = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data00109B = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data00109D = [[NSData alloc] initWithBytes:"\x01" length:length];
            
            // Setlist
                        
            NSData *data040A6B = [[NSData alloc] initWithBytes:"\x03" length:length]; 
            NSData *data040A6D = [[NSData alloc] initWithBytes:"\x21" length:length];
            NSData *data040A77 = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data040AA3 = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data040AAB = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data040AAD = [[NSData alloc] initWithBytes:"\x01" length:length];
            
            
            // Footer
            
            // Seek and Write to File
            
            NSFileHandle *modifyFile = [NSFileHandle fileHandleForUpdatingAtPath: pathToPreset];
            
            if (modifyFile == nil)
                NSLog(@"Failed to open file");
            
            // Header
            
            [modifyFile seekToFileOffset: 0x00000B];
            [modifyFile writeData: data00000B];
            
            [modifyFile seekToFileOffset: 0x00000D];
            [modifyFile writeData: data00000D];
            
            [modifyFile seekToFileOffset: 0x000017];
            [modifyFile writeData: data000017];
            
            [modifyFile seekToFileOffset: 0x000033];
            [modifyFile writeData: data000033];
            
            [modifyFile seekToFileOffset: 0x000035];
            [modifyFile writeData: data000035];
            
            [modifyFile seekToFileOffset: 0x00003F];
            [modifyFile writeData: data00003F];
            
            [modifyFile seekToFileOffset: 0x00006B];
            [modifyFile writeData: data00006B];
            
            [modifyFile seekToFileOffset: 0x000073];
            [modifyFile writeData: data000073];
            
            [modifyFile seekToFileOffset: 0x000075];
            [modifyFile writeData: data000075];
            
            // Content 1-8
            
            for (int j=0; j<8; j++) {
                for (int i=0; i<64; i++) {
                    [modifyFile seekToFileOffset: ((0x000E5A + (j * 0x040A38)) + (i * 0x001028))];
                    [modifyFile writeData: guitarIn];
                    
                    [modifyFile seekToFileOffset: ((0x001086 + (j * 0x040A38)) + (i * 0x001028))];
                    [modifyFile writeData: sourceOne];
                    
                    [modifyFile seekToFileOffset: ((0x001087 + (j * 0x040A38)) + (i * 0x001028))];
                    [modifyFile writeData: sourceTwo];
                    
                    [modifyFile seekToFileOffset: ((0x001093 + (j * 0x040A38)) + (i * 0x001028))];
                    [modifyFile writeData: data001093];
                    
                    [modifyFile seekToFileOffset: ((0x00109B + (j * 0x040A38)) + (i * 0x001028))];
                    [modifyFile writeData: data00109B];
                    
                    [modifyFile seekToFileOffset: ((0x00109D + (j * 0x040A38)) + (i * 0x001028))];
                    [modifyFile writeData: data00109D];
                }
            }
            
            // Setlist 2-8
            
            for (int i=0; i<7; i++) {                
                [modifyFile seekToFileOffset: (0x040A6B + (i * 0x40A38))];
                [modifyFile writeData: data040A6B];
                
                [modifyFile seekToFileOffset: (0x040A6D + (i * 0x40A38))];
                [modifyFile writeData: data040A6D];
                
                [modifyFile seekToFileOffset: (0x040A77 + (i * 0x40A38))];
                [modifyFile writeData: data040A77];
                
                [modifyFile seekToFileOffset: (0x040AA3 + (i * 0x40A38))];
                [modifyFile writeData: data040AA3];
                
                [modifyFile seekToFileOffset: (0x040AAB + (i * 0x40A38))];
                [modifyFile writeData: data040AAB];
                
                [modifyFile seekToFileOffset: (0x040AAD + (i * 0x40A38))];
                [modifyFile writeData: data040AAD];
            }

            // Footer
            
            // Close File
            
            
            [data00000B release];
            data00000B = nil;
            
            [data00000D release];
            data00000D = nil;
            
            [data000017 release];
            data000017 = nil;
            
            [data000033 release];
            data000033 = nil;
            
            [data000035 release];
            data000035 = nil;
            
            [data00003F release];
            data00003F = nil;
            
            [data00006B release];
            data00006B = nil;
            
            [data000073 release];
            data000073 = nil;
            
            [data000075 release];
            data000075 = nil;
            
            [data001093 release];
            data001093 = nil;
            
            [data00109B release];
            data00109B = nil;
            
            [data00109D release];
            data00109D = nil;
            
            [data040A6B release];
            data040A6B = nil;
            
            [data040A6D release];
            data040A6D = nil;
            
            [data040A77 release];
            data040A77 = nil;
            
            [data040AA3 release];
            data040AA3 = nil;
            
            [data040AAB release];
            data040AAB = nil;
            
            [data040AAD release];
            data040AAD = nil;
            
            [modifyFile closeFile];
        }
    }
    [pool release];        
} 

- (void) modifySetlistFiles: (NSArray *) presetFiles fromPath:(NSURL *)path {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    @autoreleasepool {
        
        for (int i = 0; i < [presetFiles count] ; i = i+1) {
            
            NSString *pathToPreset;
            
            NSString *presetName = [presetFiles objectAtIndex:i];
            pathToPreset = [[path path] stringByAppendingPathComponent:presetName];
                        
            //NSLog(@"File to be modified: %@", fullPathPreset);
            
            // Header
            
            NSData *data00000B = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data00000D = [[NSData alloc] initWithBytes:"\x01" length:length]; 
            NSData *data000017 = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data000043 = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data00004B = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data00004D = [[NSData alloc] initWithBytes:"\x01" length:length];
            
            // Content
            
            NSData *data00106B = [[NSData alloc] initWithBytes:"\x28" length:length];
            NSData *data001073 = [[NSData alloc] initWithBytes:"\x03" length:length];
            NSData *data001075 = [[NSData alloc] initWithBytes:"\x01" length:length];
            
            // Footer
            
            // Seek and Write to File
            
            NSFileHandle *modifyFile = [NSFileHandle fileHandleForUpdatingAtPath: pathToPreset];
            
            if (modifyFile == nil)
                NSLog(@"Failed to open file");
            
            // Header
            
            [modifyFile seekToFileOffset: 0x00000B];
            [modifyFile writeData: data00000B];
            
            [modifyFile seekToFileOffset: 0x00000D];
            [modifyFile writeData: data00000D];
            
            [modifyFile seekToFileOffset: 0x000017];
            [modifyFile writeData: data000017];
            
            [modifyFile seekToFileOffset: 0x000043];
            [modifyFile writeData: data000043];
            
            [modifyFile seekToFileOffset: 0x00004B];
            [modifyFile writeData: data00004B];
            
            [modifyFile seekToFileOffset: 0x00004D];
            [modifyFile writeData: data00004D];
            
            
            // Content
            
            for (int i=0; i<64; i++) {
                
                [modifyFile seekToFileOffset: (0x000E32 + (i * 0x001028))];
                [modifyFile writeData: guitarIn];
                
                [modifyFile seekToFileOffset: (0x00105E + (i * 0x001028))];
                [modifyFile writeData: sourceOne];
                
                [modifyFile seekToFileOffset: (0x00105F + (i * 0x001028))];
                [modifyFile writeData: sourceTwo];
                
                [modifyFile seekToFileOffset: (0x00106B + (i * 0x001028))];
                [modifyFile writeData: data00106B];
                
                [modifyFile seekToFileOffset: (0x001073 + (i * 0x001028))];
                [modifyFile writeData: data001073];
                
                [modifyFile seekToFileOffset: (0x001075 + (i * 0x001028))];
                [modifyFile writeData: data001075];
            }
            
            // Footer
            
            // Close File
            
            [data00000B release];
            data00000B = nil;
            
            [data00000D release];
            data00000D = nil;
            
            [data000017 release];
            data000017 = nil;
            
            [data000043 release];
            data000043 = nil;
            
            [data00004B release];
            data00004B = nil;
            
            [data00004D release];
            data00004D = nil;
            
            [data00106B release];
            data00106B = nil;
            
            [data001073 release];
            data001073 = nil;
            
            [data001075 release];
            data001075 = nil;
            
            [modifyFile closeFile];
        }
    }
    [pool release];        
}

- (BOOL) poti:(NSFileHandle *)sourceFile targetfile:(NSFileHandle *)targetFile sourcePosition:(int)sourcePosition targetPosition:(int)targetPosition {
    
    float multiPoti = 0x7FFF;
    char hexOut1[1], hexOut2[1];
    
    NSData *databuffer;
    
    [sourceFile seekToFileOffset:sourcePosition];
    databuffer = [sourceFile readDataOfLength:sizeof(float)];
    
    // Parse 4 Bytes to float
    
    NSUInteger len = [databuffer length];
    char *byteData = (char*)malloc(len);
    memcpy(byteData, [databuffer bytes], len);
    
    
    union {
        char chars[4];
        float f;
    } ufloat;
    
    for (int i = 0; i < 4; i++)
        ufloat.chars[3-i] = byteData[i];
    float fPoti = ufloat.f;

    float floatCalculated = fPoti * multiPoti;
    
    // Convert to int (2 Bytes)
    
    int intToWrite = (int) floatCalculated;
    
    // Write to file
    
    //NSLog( @"%f", fPoti);
    //NSLog(@"%p", [databuffer bytes]);
    //NSLog(@"bytes in hex: %@", [databuffer description]);
    
    hexOut1[0] = (intToWrite & 0xFF);
    hexOut2[0] = ((intToWrite >> 8) & 0xFF);
    [targetFile seekToFileOffset:targetPosition];
    [targetFile writeData:[NSData dataWithBytes:hexOut2 length:length]];
    [targetFile writeData:[NSData dataWithBytes:hexOut1 length:length]];
    
    free(byteData);
    return true;
}

- (BOOL) potiReversed:(NSFileHandle *)sourceFile targetfile:(NSFileHandle *)targetFile sourcePosition:(int)sourcePosition targetPosition:(int)targetPosition {
    
    float multiPoti = 0x7FFF;
    char hexOut1[1], hexOut2[1];
    
    NSData *databuffer;
    
    [sourceFile seekToFileOffset:sourcePosition];
    databuffer = [sourceFile readDataOfLength:sizeof(float)];
    
    // Parse 4 Bytes to float
    
    NSUInteger len = [databuffer length];
    char *byteData = (char*)malloc(len);
    memcpy(byteData, [databuffer bytes], len);
    
    union {
        char chars[4];
        float f;
    } ufloat;
    
    for (int i = 0; i < 4; i++)
        ufloat.chars[3-i] = byteData[i];
    float fPoti = ufloat.f;
        
    float floatPreCalculated = (fPoti * multiPoti);
    float floatCalculated = (floatPreCalculated - multiPoti);
    
    // Convert to int (2 Bytes)
    
    int intToWrite = (int) floatCalculated;
    
    // Write to file
    
    //NSLog( @"%f", fPoti);
    //NSLog(@"%p", [databuffer bytes]);
    //NSLog(@"bytes in hex: %@", [databuffer description]);
    
    hexOut1[0] = (intToWrite & 0xFF);
    hexOut2[0] = ((intToWrite >> 8) & 0xFF);
    [targetFile seekToFileOffset:targetPosition];
    [targetFile writeData:[NSData dataWithBytes:hexOut2 length:length]];
    [targetFile writeData:[NSData dataWithBytes:hexOut1 length:length]];
    
    free(byteData);
    return true;
}

- (BOOL) potiDecibel:(NSFileHandle *)sourceFile targetfile:(NSFileHandle *)targetFile sourcePosition:(int)sourcePosition targetPosition:(int)targetPosition {
    
    char hexOut1[1], hexOut2[1];
    
    NSData *databuffer;
    
    [sourceFile seekToFileOffset:sourcePosition];
    databuffer = [sourceFile readDataOfLength:sizeof(float)];
    
    // Parse 4 Bytes to float
    
    NSUInteger len = [databuffer length];
    char *byteData = (char*)malloc(len);
    memcpy(byteData, [databuffer bytes], len);
    
    union {
        char chars[4];
        float f;
    } ufloat;
    
    for (int i = 0; i < 4; i++)
        ufloat.chars[3-i] = byteData[i];
    float fPoti = ufloat.f;
    
    // Convert to int (2 Bytes) - negative
    
    uint intToWrite = (int) 0x10000 - (0x25E8 * (fPoti));    
    
    // Write to file
    
    //NSLog( @"%f", fPoti);
    //NSLog(@"%p", [databuffer bytes]);
    //NSLog(@"bytes in hex: %@", [databuffer description]);
    
    hexOut1[0] = (intToWrite & 0xFF);
    hexOut2[0] = ((intToWrite >> 8) & 0xFF);
    [targetFile seekToFileOffset:targetPosition];
    [targetFile writeData:[NSData dataWithBytes:hexOut2 length:length]];
    [targetFile writeData:[NSData dataWithBytes:hexOut1 length:length]];
    
    free(byteData);
    return true;
}

- (BOOL) potiByte:(NSFileHandle *)sourceFile targetfile:(NSFileHandle *)targetFile sourcePosition:(int)sourcePosition targetPosition:(int)targetPosition {
    
    NSData *databuffer;
    
    [sourceFile seekToFileOffset:sourcePosition];
    databuffer = [sourceFile readDataOfLength:sizeof(float)];
    
    // Parse 4 Bytes to float
    
    NSUInteger len = [databuffer length];
    char *byteData = (char*)malloc(len);
    memcpy(byteData, [databuffer bytes], len);
    
    
    union {
        char chars[4];
        float f;
    } ufloat;
    
    for (int i = 0; i < 4; i++)
        ufloat.chars[3-i] = byteData[i];
    float fPoti = ufloat.f;
    
    // Convert to char (1 Byte)
    
    float floatCalculated = (fPoti * 255);
    char charToWrite[1] = { (char) floatCalculated };
    
    // Write to file
    
    //NSLog( @"%f", fPoti);
    //NSLog(@"%p", [databuffer bytes]);
    //NSLog(@"bytes in hex: %@", [databuffer description]);
    
    [targetFile seekToFileOffset:targetPosition];
    [targetFile writeData:[NSData dataWithBytes:charToWrite length:length]];
    
    free(byteData);
    return true;
}

- (void) copy:(NSURL *)path {
    
    if ([chkbxMakeBackup state] == NSOnState) {
        
        backupPath = [[path path] stringByAppendingPathComponent:@"backup"];
        NSError *err = NULL;
        NSFileManager *fileManager= [NSFileManager defaultManager]; 
        
        BOOL directoryExsits;
        if (![fileManager fileExistsAtPath:backupPath isDirectory:&directoryExsits] && directoryExsits) {
            BOOL backup = [fileManager createDirectoryAtPath:backupPath withIntermediateDirectories:NO attributes:nil error:&err];
            if(!backup)
                @throw [NSException exceptionWithName:[err localizedDescription] reason:[err localizedFailureReason] userInfo:nil];
        }

        @try {
            if ([chkbxPatchH5e state] == NSOnState) {
                [self copyFiles:onlyH5eFiles fromPath:path];
            }
            if ([chkbxPatchHbe state] == NSOnState) {
                [self copyFiles:onlyHbeFiles fromPath:path];
            }
            if ([chkbxPatchH5b state] == NSOnState) {
                [self copyFiles:onlyH5bFiles fromPath:path];
            }
            if ([chkbxPatchHbb state] == NSOnState) {
                [self copyFiles:onlyHbbFiles fromPath:path];
            }
            if ([chkbxPatchH5s state] == NSOnState) {
                [self copyFiles:onlyH5sFiles fromPath:path];
            }
            if ([chkbxPatchHbs state] == NSOnState) {
                [self copyFiles:onlyHbsFiles fromPath:path];
            }
        }
        @catch (NSException *exception) {
            NSLog(@"main: Caught %@: %@", [exception name], [exception reason]);
        }
        @finally {
            //
        }
    } else if ([chkbxMakeBackup300 state] == NSOnState) {
        backupPath = [[path path] stringByAppendingPathComponent:@"backup"];
        NSError *err = NULL;
        NSFileManager *fileManager= [NSFileManager defaultManager]; 
        
        BOOL directoryExsits;
        if (![fileManager fileExistsAtPath:backupPath isDirectory:&directoryExsits] && directoryExsits) {
            BOOL backup = [fileManager createDirectoryAtPath:backupPath withIntermediateDirectories:NO attributes:nil error:&err];
            if(!backup)
                @throw [NSException exceptionWithName:[err localizedDescription] reason:[err localizedFailureReason] userInfo:nil];
        }
        
        @try {
            if ([chkbxPatchH3e state] == NSOnState) {
                [self copyFiles:onlyH5eFiles fromPath:path];
            }
            if ([chkbxPatchH4e state] == NSOnState) {
                [self copyFiles:onlyH5eFiles fromPath:path];
            }
        }
        @catch (NSException *exception) {
            NSLog(@"main: Caught %@: %@", [exception name], [exception reason]);
        }
        @finally {
            //
        }
    }
}

- (void) copyFiles: (NSArray *) presetFiles fromPath:(NSURL *)path {
    
    NSError *err;

    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    @autoreleasepool {
        
        for (int i = 0; i < [presetFiles count] ; i = i+1) {
            
            NSString *presetFrom;
            NSString *presetTo;
            NSFileManager *filemgr = [NSFileManager defaultManager];

            NSString *presetName = [presetFiles objectAtIndex:i];
            presetFrom = [[path path] stringByAppendingPathComponent:presetName];
            presetTo = [backupPath stringByAppendingPathComponent:presetName];
                                                
            BOOL success = [filemgr copyItemAtPath: presetFrom toPath: presetTo error: &err];
            
            if (!success) {
                @throw [NSException exceptionWithName:[err localizedDescription] reason:[err localizedFailureReason] userInfo:nil];
            }
        }
    }
    [pool release];        
}

- (void) rename: (NSURL *)path {
    presetsMoved = 0;

    // state == 0 : hbe->h5e ;state == 1 : h5e->hbe
    if ([[renameRadioPatches cellWithTag:1] state] == 1) {
        [self renameFiles:onlyH5eFiles fromPath:path extensionRenamedFrom:H5E_EXTENSION extensionRenamedTo:HBE_EXTENSION];
        presetsMoved = [onlyH5eFiles count];
    }
    if ([[renameRadioPatches cellWithTag:0] state] == 1) {
        [self renameFiles:onlyHbeFiles fromPath:path extensionRenamedFrom:HBE_EXTENSION extensionRenamedTo:H5E_EXTENSION];
        presetsMoved = presetsMoved + [onlyHbeFiles count];
    }
    
    if ([[renameRadioBundles cellWithTag:1] state] == 1) {
        [self renameFiles:onlyH5bFiles fromPath:path extensionRenamedFrom:H5B_EXTENSION extensionRenamedTo:HBB_EXTENSION];
        presetsMoved = presetsMoved + [onlyH5bFiles count];
    }
    if ([[renameRadioBundles cellWithTag:0] state] == 1) {
        [self renameFiles:onlyHbbFiles fromPath:path extensionRenamedFrom:HBB_EXTENSION extensionRenamedTo:H5B_EXTENSION];
        presetsMoved = presetsMoved + [onlyHbbFiles count];
    }
    
    if ([[renameRadioSetlists cellWithTag:1] state] == 1) {
        [self renameFiles:onlyH5sFiles fromPath:path extensionRenamedFrom:H5S_EXTENSION extensionRenamedTo:HBS_EXTENSION];
        presetsMoved = presetsMoved + [onlyH5sFiles count];
    }
    if ([[renameRadioSetlists cellWithTag:0] state] == 1) {
        [self renameFiles:onlyHbsFiles fromPath:path extensionRenamedFrom:HBS_EXTENSION extensionRenamedTo:H5S_EXTENSION];
        presetsMoved = presetsMoved + [onlyHbsFiles count];
    }
}
    

- (void) renameFiles: (NSArray *) presetFilesToBeRenamed fromPath:(NSURL *)pathOfPresetFiles extensionRenamedFrom:(NSString *)oldEnding extensionRenamedTo: (NSString *)newEnding {
    
    NSError *err;
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    @autoreleasepool {
        
        for (int i = 0; i < [presetFilesToBeRenamed count] ; i = i+1) {
            
            NSString *oldPreset;
            NSString *newPreset;
            NSFileManager *filemgr = [NSFileManager defaultManager];
            
            NSString *presetNameNoExtension = [[presetFilesToBeRenamed objectAtIndex:i] stringByDeletingPathExtension];
            oldPreset = [[[pathOfPresetFiles path] stringByAppendingPathComponent:presetNameNoExtension] stringByAppendingPathExtension:oldEnding];
            newPreset = [[[pathOfPresetFiles path] stringByAppendingPathComponent:presetNameNoExtension] stringByAppendingPathExtension:newEnding];
            
            BOOL success = [filemgr moveItemAtPath: oldPreset toPath: newPreset error: &err];
            
            if (!success) {
                @throw [NSException exceptionWithName:[err localizedDescription] reason:[err localizedFailureReason] userInfo:nil];
            }
        }
    }
    [pool release];   
}

- (void) changeTextAfterRun {
    [appRunned setStringValue: @""];
    
    NSString *StringDone;
    NSString *StringOne = @"Done: ";
    NSString *StringTwo = [NSString stringWithFormat:@"%d", presetsPatched];
    NSString *StringThree = @" files patched and ";
    NSString *StringFour = [NSString stringWithFormat:@"%d", presetsMoved];
    NSString *StringFive = @" files renamed.";
    NSString *StringSix = @" Backup created.";
    
    if ([chkbxMakeBackup state] == NSOnState) {
        StringDone = [[[[[StringOne stringByAppendingString: StringTwo] stringByAppendingString: StringThree ] stringByAppendingString: StringFour] stringByAppendingString: StringFive] stringByAppendingString: StringSix];
    } else {
        StringDone = [[[[StringOne stringByAppendingString: StringTwo] stringByAppendingString: StringThree ] stringByAppendingString: StringFour] stringByAppendingString: StringFive];
    }

    [appRunned setStringValue: StringDone];

}

- (void) changeTextAfterRun300 {
    [appRunned300 setStringValue: @""];
    
    NSString *StringDone;
    NSString *StringOne = @"Done: ";
    NSString *StringTwo = [NSString stringWithFormat:@"%d", presetsPatched];
    NSString *StringThree = @" files translated.";
    NSString *StringFour = @" Backup created.";
    
    if ([chkbxMakeBackup state] == NSOnState) {
        StringDone = [[[StringOne stringByAppendingString: StringTwo] stringByAppendingString: StringThree ] stringByAppendingString: StringFour];
    } else {
        StringDone = [[StringOne stringByAppendingString: StringTwo] stringByAppendingString: StringThree ];
    }
    
    [appRunned300 setStringValue: StringDone];
    
}

- (IBAction)editPresetsPressed:(id)sender {
    if ([chkbxEditPresets state] == NSOnState) {
        [cbInputSourceOne setEnabled:YES];
        [cbInputSourceTwo setEnabled:YES];
        [cbGuitarIn setEnabled:YES];
    } else {
        [cbInputSourceOne setEnabled:NO];
        [cbInputSourceTwo setEnabled:NO];
        [cbGuitarIn setEnabled:NO];
    }
}

- (IBAction)performRun:(id)sender {
    [self initialize];
    [self getFiles:presetFromDirectory pressedFrom:@"Desktop"];
    [self copy:presetFromDirectory];
    [self processAdvancedTab];
    [self modify:presetFromDirectory pressedFrom:@"Desktop"];
    [self rename:presetFromDirectory];
    [self changeTextAfterRun];
    [self destruct];
}

- (IBAction)performRun300:(id)sender {
    [self initialize];
    [self getFiles:presetFromDirectory pressedFrom:@"300"];
    [self copy:presetFromDirectory];
    [self modify:presetFromDirectory pressedFrom:@"300"];
    [self changeTextAfterRun300];
    [self destruct];
}

@end
