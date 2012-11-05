//
//  VUIGridView.h
//  Youplay
//
//  Created by Slavik Shen on 12/13/11.
//  Copyright (c) 2011 apollobrowser.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "VUIGridCellView.h"
#import "VUIGridViewLayoutDelegate.h"

#define SRELEASE(x) { [x release]; x = nil; }
#define IS_PIXEL_COORDINATE_CHANGED(a,b) (ABS(a-b)>1)
#define IS_SIZE_CHANGED(p,n) (ABS(p.width-n.width)>1||ABS(p.height-n.height)>1)
#define IS_POSITION_CHANGED(p,n) (ABS(p.x-n.x)>1||ABS(p.y-n.y)>1)

#define IS_DIFFERENT_FRAME(p,n) (IS_SIZE_CHANGED(p.size,n.size)||IS_POSITION_CHANGED(p.origin,n.origin))

#define VUIGRIDVIEW_CELL_ANI_DURATION (0.5f)

#define VUIGRIDVIEW_DEFAULT_CELL_SIZE CGSizeMake(320, 240)
#define VUIGRIDVIEW_DEFAULT_CELL_SPACING CGSizeMake(1, 20)

@class VUIGridView;

@protocol VUIGridViewDataSource <NSObject>

- (NSInteger)numberOfCellOfGridView:(VUIGridView*)gridView;

@optional

// sync create and set cell
- (VUIGridCellView*)gridView:(VUIGridView*)gridView cellAtIndex:(NSUInteger)index;

// async create and set cell
- (void)gridView:(VUIGridView*)gridView upgradeCellAtIndex:(NSUInteger)index;

@end

@protocol VUIGridViewDelegate <NSObject, UIScrollViewDelegate>

@optional
- (void)gridView:(VUIGridView *)gridView didSelectCellAtIndexPath:(NSUInteger)index;
- (void)gridView:(VUIGridView *)gridView didShowCellAtIndex:(NSUInteger)index;
- (void)gridView:(VUIGridView *)gridView didHideCellAtIndex:(NSUInteger)index;

@end


@interface VUIGridView : UIView {

@protected
	NSMutableSet* _visibleCells;
	NSMutableSet* _recycledCells;
    
    BOOL _needCheckVisibility;
    
    NSUInteger _numberOfCells;
    NSUInteger _numberOfColumns;
    NSUInteger _numberOfRows;
    
    BOOL _delegateWillResponseClick;
	BOOL _dataSourceWillUpgradeContent;
    
    #ifdef ENABLE_GRIDVIEW_ANIMATION_CHANGE
    
    BOOL _needAnimateChange;
   
    #endif

    NSUInteger _changeStartIndex;
    
}

@property(nonatomic,readonly,assign) CGSize cellSize;
@property(nonatomic,readonly,assign) CGSize cellSpacing;

@property(nonatomic,assign) IBOutlet id<VUIGridViewDataSource> dataSource;
@property(nonatomic,assign) IBOutlet id<VUIGridViewDelegate> delegate;

@property(nonatomic,readonly,assign) UILabel* emtpyHintLabel;

@property(nonatomic,readonly,assign) UIScrollView* scrollView;

@property(nonatomic,readonly,assign) NSUInteger numberOfCells;
@property(nonatomic,readonly,assign) NSUInteger numberOfColumns;
@property(nonatomic,readonly,assign) NSUInteger numberOfRows;

- (void)setup;

- (void)reloadData;

- (void)setCellSize:(CGSize)cellSize andSpacing:(CGSize)cellSpacing animate:(BOOL)animated;

- (void)insertCellAtIndex:(NSUInteger)index animated:(BOOL)animated;
- (void)removeCellAtIndex:(NSUInteger)index animated:(BOOL)animated;
- (void)reloadCellAtIndex:(NSUInteger)index animated:(BOOL)animated;

- (id)dequeueGridCellViewFromPool:(NSString*)cellID;

- (id)cellAtIndex:(NSUInteger)index;

@end

