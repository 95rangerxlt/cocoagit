//
//  GITRepo.h
//  CocoaGit
//
//  Created by Geoffrey Garside on 05/08/2008.
//  Copyright 2008 ManicPanda.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GITObjectStore.h"
#import "GITObject.h"
#import "GITCommit.h"
#import "GITTree.h"
#import "GITBlob.h"
#import "GITTag.h"

/*! A repository of git objects.
 * This class serves to encapsulate the access to the
 * objects of a repository.
 * \todo Consider the lifetime of this object. Is it going
 * to be better to retain the repo in the objects instead
 * of copying it. Should we enforce this by changing
 * -copyWithZone: to just return the retained instance of
 * GITRepo or should we leave it capable of being copied
 * but change our usage of it to retains?
 */
@interface GITRepo : NSObject <NSCopying>
{
    NSString * root;    //!< Path to the repository root
    NSString * desc;    //!< Description of the repository
                        // Interesting issue here the function used for
                        // an object to print itself is -description
    GITObjectStore * store;     //!< The store which will be used to find objects
}

@property(readonly,copy) NSString * root;
@property(readonly,copy) NSString * desc;

/*! Creates and returns a repo object with the provided root.
 * \param repoRoot The path, relative or absolute, to the repository root.
 * \return A repo object with the provided root.
 */
- (id)initWithRoot:(NSString*)repoRoot;

/*! Creates and returns a repo object with the provided root.
 * \param repoRoot The path, relative or absolute, to the repository root.
 * \param isBare Flag indicating if the repository is bare.
 * \return A repo object with the provided root.
 */
- (id)initWithRoot:(NSString*)repoRoot bare:(BOOL)isBare;

/*! Returns a new instance that's a copy of the receiver.
 * \internal
 * This will create a new instance of the GITObjectStore for the receiver.
 * \param zone The zone identifies an area of memory from which to allocate
 * for the new instance. If <tt>zone</tt> is <tt>NULL</tt>, the new instance
 * is allocated from the default zone, which is returned from the function
 * <tt>NSDefaultMallocZone</tt>.
 */
- (id)copyWithZone:(NSZone*)zone;

/*
- (NSArray*)branches;
- (NSArray*)commits;
- (NSArray*)tags;

- (GITBranch*)head;
- (GITBranch*)master;
- (GITBranch*)branchWithName:(NSString*)name;

- (GITTag*)tagWithName:(NSString*)name;
*/

#pragma mark -
#pragma mark Internal Methods (Deprecated)
/*! Returns the raw content data for an object.
 * \attention This method does not do anything to verify the
 * size or type of the object being returned.
 * \param sha1 Name of the object.
 * \return Data containing the content of the object
 * \deprecated Superceeded by -objectWithSha1:error:
 */
- (NSData*)dataWithContentsOfObject:(NSString*)sha1;

/*! Returns the content data for an object.
 * The <tt>expectedType</tt> is used to check the type identifier in the file
 * is of a certain value. If the object referred to by <tt>sha1</tt> is not of
 * the correct type then <tt>nil</tt> is returned.
 * \param sha1 Name of the objects
 * \param expectedType String used to check the object is of a specific type
 * \return Data containing the content of the object or nil if not of expected type
 * \deprecated Superceeded by -objectWithSha1:type:error:
 */
- (NSData*)dataWithContentsOfObject:(NSString*)sha1 type:(NSString*)expectedType;

#pragma mark -
#pragma mark Deprecated Loaders
/*! Returns an object identified by the given sha1.
 * \param sha1 The identifier of the object to load
 * \return A object with the given sha1 or nil if it cannot be found.
 * \deprecated Use -objectWithSha1:error: instead
 */
- (GITObject*)objectWithSha1:(NSString*)sha1;

/*! Returns a commit object identified by the given sha1.
 * \param sha1 The identifier of the commit to load
 * \return A commit object with the given sha1 or nil if it cannot be found.
 * \deprecated Use -commitWithSha1:error: instead
 */
- (GITCommit*)commitWithSha1:(NSString*)sha1;

/*! Returns a blob object identified by the given sha1.
 * \param sha1 The identifier of the blob to load
 * \return A blob object with the given sha1 or nil if it cannot be found.
 * \deprecated Use -blobWithSha1:error: instead
 */
- (GITBlob*)blobWithSha1:(NSString*)sha1;

/*! Returns a tree object identified by the given sha1.
 * \param sha1 The identifier of the tree to load
 * \return A tree object with the given sha1 or nil if it cannot be found.
 * \deprecated Use -treeWithSha1:error: instead
 */
- (GITTree*)treeWithSha1:(NSString*)sha1;

/*! Returns a tag object identified by the given sha1.
 * \param sha1 The identifier of the tag to load
 * \return A tag object with the given sha1 or nil if it cannot be found.
 * \deprecated Use -tagWithSha1:error: instead
 */
- (GITTag*)tagWithSha1:(NSString*)sha1;

#pragma mark -
#pragma mark Error Aware Loaders
/*! Returns a commit object identified by the given sha1.
 * \param sha1 The identifier of the commit to load
 * \param[out] error Contains the error if nil return value
 * \return A commit object with the given sha1 or nil if it cannot be found.
 */
- (GITCommit*)commitWithSha1:(NSString*)sha1 error:(NSError**)error;

/*! Returns a blob object identified by the given sha1.
 * \param sha1 The identifier of the blob to load
 * \param[out] error Contains the error if nil return value
 * \return A blob object with the given sha1 or nil if it cannot be found.
 */
- (GITBlob*)blobWithSha1:(NSString*)sha1 error:(NSError**)error;

/*! Returns a tree object identified by the given sha1.
 * \param sha1 The identifier of the tree to load
 * \param[out] error Contains the error if nil return value
 * \return A tree object with the given sha1 or nil if it cannot be found.
 */
- (GITTree*)treeWithSha1:(NSString*)sha1 error:(NSError**)error;

/*! Returns a tag object identified by the given sha1.
 * \param sha1 The identifier of the tag to load
 * \param[out] error Contains the error if nil return value
 * \return A tag object with the given sha1 or nil if it cannot be found.
 */
- (GITTag*)tagWithSha1:(NSString*)sha1 error:(NSError**)error;

/*! Returns an object identified by the given sha1.
 * \param sha1 The identifier of the object to load
 * \param[out] error Contains the error if nil return value
 * \return A object with the given sha1 or nil if it cannot be found.
 */
- (GITObject*)objectWithSha1:(NSString*)sha1 error:(NSError**)error;

/*! Returns an object identified by the given sha1.
 * \param sha1 The identifier of the object to load
 * \param type The GITObjectType to return, GITObjectTypeUnknown if not known.
 * \param[out] error Contains the error if nil return value
 * \return A object with the given sha1 or nil if it cannot be found.
 */
- (GITObject*)objectWithSha1:(NSString*)sha1 type:(GITObjectType)type error:(NSError**)error;

#pragma mark -
#pragma mark Low Level Loader
/*! \see GITObjectStore */
- (BOOL)loadObjectWithSha1:(NSString*)sha1 intoData:(NSData**)data
                      type:(GITObjectType*)type error:(NSError**)error;
@end
