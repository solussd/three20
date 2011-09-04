//
// Copyright 2009-2010 Facebook
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// UI
#import "Three20UI/TTLauncherPersistenceMode.h"

@protocol TTLauncherViewDelegate;
@class TTPageControl;
@class TTLauncherButton;
@class TTLauncherItem;
@class TTLauncherHighlightView;

@interface TTLauncherView : UIView <UIScrollViewDelegate> {
  NSMutableArray* _pages;

  NSInteger       _columnCount;
  NSInteger       _rowCount;

  NSString*       _prompt;

  NSMutableArray* _buttons;
  UIScrollView*   _scrollView;

  TTPageControl*   _pager;

  NSTimer*        _editHoldTimer;
  NSTimer*        _springLoadTimer;

  TTLauncherButton* _dragButton;
  UITouch*          _dragTouch;
  NSInteger         _positionOrigin;
  CGPoint           _dragOrigin;
  CGPoint           _touchOrigin;

  TTLauncherHighlightView* _highlightView;

  BOOL _editing;
  BOOL _springing;
  BOOL _editable;

  NSString*                   _persistenceKey;
  TTLauncherPersistenceMode   _persistenceMode;

  id<TTLauncherViewDelegate> _delegate;
    
  UIView *bannerView; 
}

@property (nonatomic, assign) id<TTLauncherViewDelegate> delegate;

@property (nonatomic, copy) NSArray* pages;

@property (nonatomic) NSInteger columnCount;

@property (nonatomic, readonly) NSInteger rowCount;

@property (nonatomic) NSInteger currentPageIndex;

@property (nonatomic, copy) NSString* prompt;

@property (nonatomic, readonly) BOOL editing;
@property (nonatomic, assign) BOOL editable;

/**
 * The key to use for storing persistence information.
 *
 * @default launcherViewPages
 */
@property (nonatomic, copy) NSString* persistenceKey;

/**
 * How buttons are automatically persisted on termination and restored on launch.
 *
 * @default TTLauncherPersistenceModeNone
 */
@property (nonatomic) TTLauncherPersistenceMode persistenceMode;

@property (nonatomic, retain) UIView *bannerView;

- (void)addItem:(TTLauncherItem*)item animated:(BOOL)animated;

- (void)removeItem:(TTLauncherItem*)item animated:(BOOL)animated;

- (TTLauncherItem*)itemWithURL:(NSString*)URL;

- (NSIndexPath*)indexPathOfItem:(TTLauncherItem*)item;

- (void)scrollToItem:(TTLauncherItem*)item animated:(BOOL)animated;

- (void)beginEditing;

- (void)endEditing;

/**
 * Persists all pages & buttons to user defaults.
 */
- (void)persistLauncherItems;

/**
 * Restores all pages & button from user defaults and returns if sucess
 */
- (BOOL)restoreLauncherItems;

/**
 * Erases all data stored in user defaults.
 */
- (void)resetDefaults;

/**
 * Dims the launcher view except for a transparent circle around the given item. The given text
 * will also be shown center-aligned below or above the circle, as appropriate. The item can be
 * tapped while the overlay is up; tapping anywhere else on the overlay simply dismisses the
 * overlay and does not pass the event through.
 */
- (void)beginHighlightItem:(TTLauncherItem*)item withText:(NSString*)text;

/**
 * Removes the highlighting overlay introduced by -beginHighlightItem:withText:. This will be done
 * automatically if the user taps anywhere on the overlay except the transparent circle.
 */
- (void)endHighlightItem:(TTLauncherItem*)item;

@end
