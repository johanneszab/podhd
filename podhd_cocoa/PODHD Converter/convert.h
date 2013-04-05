//
//  convert.h
//  PODHD Converter
//
//  Created by xen on 5/3/12.
//  Copyright (c) 2012 www.jzab.de. All rights reserved.
//

#import <Foundation/Foundation.h>

// constants

extern NSString * const H5E_EXTENSION;
extern NSString * const HBE_EXTENSION;

@interface convert : NSObject {
    
// outlets
    
    // HD Desktop

    IBOutlet NSTextField *appRunned;
    IBOutlet NSTextField *presetFromDirectoryLabel;
    
    IBOutlet NSButton *chkbxPatchH5e;
    IBOutlet NSButton *chkbxPatchHbe;
    IBOutlet NSButton *chkbxPatchH5b;
    IBOutlet NSButton *chkbxPatchHbb;
    IBOutlet NSButton *chkbxPatchH5s;
    IBOutlet NSButton *chkbxPatchHbs;
    IBOutlet NSButton *chkbxMakeBackup;
    
    IBOutlet NSButton *chkbxEditPresets;
    IBOutlet NSComboBox *cbInputSourceOne;
    IBOutlet NSComboBox *cbInputSourceTwo;
    IBOutlet NSComboBox *cbGuitarIn;
    
    IBOutlet NSMatrix *renameRadioPatches;
    IBOutlet NSMatrix *renameRadioBundles;
    IBOutlet NSMatrix *renameRadioSetlists;
    //IBOutlet NSMatrix *renameHbe;
    
    
    // HD 300
    
    IBOutlet NSTextField *appRunned300;
    IBOutlet NSTextField *presetFromDirectoryLabel300;
    
    IBOutlet NSButton *chkbxPatchH4e;
    IBOutlet NSButton *chkbxPatchH3e;
    IBOutlet NSButton *chkbxPatchH4b;
    IBOutlet NSButton *chkbxPatchH3b;
    IBOutlet NSButton *chkbxPatchH4s;
    IBOutlet NSButton *chkbxPatchH3s;
    IBOutlet NSButton *chkbxMakeBackup300;

    
// variables
        
}

// accessors

// actions

- (IBAction)browseButton:(id)sender;
- (IBAction)performRun:(id)sender;
- (IBAction)enteredDirectory:(id)sender;
- (IBAction)editPresetsPressed:(id)sender;

- (IBAction)browseButton300:(id)sender;
- (IBAction)performRun300:(id)sender;
- (IBAction)enteredDirectory300:(id)sender;


// class methods

// singleton constants (not in heap -> NSArray)

// methods

- (void) initialize;
- (void) destruct;

- (void) getFiles:(NSURL *)pathOfPresetDirectory pressedFrom:(NSString *)model;
- (void) processAdvancedTab;
- (void) modify: (NSURL *)path pressedFrom:(NSString *)model;
- (void) modifyPatchFiles: (NSArray *)presetFiles fromPath:(NSURL *)path;
- (void) modifyPatchFiles300: (NSArray *)presetFiles fromPath:(NSURL *)path toExtension:(NSString *)toExtension;
- (void) modifyBundleFiles: (NSArray *)presetFiles fromPath:(NSURL *)path;
- (void) modifySetlistFiles: (NSArray *)presetFiles fromPath:(NSURL *)path;
- (void) copy: (NSURL *)path;
- (void) copyFiles: (NSArray *)presetFiles fromPath:(NSURL *)path;
- (void) rename: (NSURL *)path;
- (void) renameFiles: (NSArray *) presetFilesToBeRenamed fromPath:(NSURL *)pathOfPresetFiles extensionRenamedFrom:(NSString *)oldEnding extensionRenamedTo: (NSString *)newEnding;

- (BOOL) poti:(NSFileHandle *)sourceFile targetfile:(NSFileHandle *)targetFile sourcePosition:(int)sourcePosition targetPosition:(int)targetPosition;
- (BOOL) potiReversed:(NSFileHandle *)sourceFile targetfile:(NSFileHandle *)targetFile sourcePosition:(int)sourcePosition targetPosition:(int)targetPosition;
- (BOOL) potiDecibel:(NSFileHandle *)sourceFile targetfile:(NSFileHandle *)targetFile sourcePosition:(int)sourcePosition targetPosition:(int)targetPosition;
- (BOOL) potiByte:(NSFileHandle *)sourceFile targetfile:(NSFileHandle *)targetFile sourcePosition:(int)sourcePosition targetPosition:(int)targetPosition;

@end
