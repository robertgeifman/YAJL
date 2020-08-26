//
//  YAJLParser.h
//  YAJL
//
//  Created by Gabriel Handford on 6/14/09.
//  Copyright 2009. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation
//  files (the "Software"), to deal in the Software without
//  restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following
//  conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.
//

@import Foundation;

@class YAJLParser;

NS_ASSUME_NONNULL_BEGIN
// MARK: - YAJLParserDelegate
@protocol YAJLParserDelegate <NSObject>
/*!
   Parser did start dictionary.
   @param parser Sender
 */
- (void)parserDidStartDictionary:(YAJLParser *)parser;

/*!
   Parser did end dictionary.
   @param parser Sender
 */
- (void)parserDidEndDictionary:(YAJLParser *)parser;

/*!
   Parser did start array.
   @param parser Sender
 */
- (void)parserDidStartArray:(YAJLParser *)parser;

/*!
   Parser did end array.
   @param parser Sender
 */
- (void)parserDidEndArray:(YAJLParser *)parser;

/*!
   Parser did map key.
   @param parser Sender
   @param key Key that was mapped
 */
- (void)parser:(YAJLParser *)parser didMapKey:(NSString *)key;

/*!
   Did add value.
   @param parser Sender
   @param value Value of type NSNull, NSString or NSNumber
 */
- (void)parser:(YAJLParser *)parser didAdd:(id)value;
@end

// Error domain for YAJL
extern NSString *const YAJLErrorDomain;
// Generic parse exception
extern NSString *const YAJLParserException;
// Parsing unsupported exception
extern NSString *const YAJLParsingUnsupportedException;
// Key in NSError userInfo for value we errored on
extern NSString *const YAJLParserValueKey;

// MARK: - YAJLParserErrorCode
typedef NS_ENUM (NSInteger, YAJLParserErrorCode) {
	// Alloc error
	YAJLParserErrorCodeAllocError = -1000,
	// Double overflow
	YAJLParserErrorCodeDoubleOverflow = -1001,
	// Integer overflow
	YAJLParserErrorCodeIntegerOverflow = -1002
};

// MARK: - YAJLParserOptions
typedef NS_ENUM (NSUInteger, YAJLParserOptions) {
	// No options
	YAJLParserOptionsNone = 0,
	// Javascript style comments will be allowed in the input (both /&asterisk; &asterisk;/ and //)
	YAJLParserOptionsAllowComments = 1 << 0,
	// Invalid UTF8 strings will cause a parse error
	YAJLParserOptionsCheckUTF8 = 1 << 1,
	// If YES will force strict precision and return integer overflow error
	YAJLParserOptionsStrictPrecision = 1 << 2,
};

// MARK: - YAJLParserStatus
typedef NS_ENUM (NSUInteger, YAJLParserStatus) {
	// No status
	YAJLParserStatusNone = 0,
	// Parsed OK
	YAJLParserStatusOK = 1,
	// Parser errored
	YAJLParserStatusError = 3
};

// MARK: - YAJLParser
/*!
   Sample usage:
   @code
   NSData *data = [NSData dataWithContentsOfFile:@"example.json"];

   YAJLParser *parser = [[YAJLParser alloc] initWithParserOptions:YAJLParserOptionsAllowComments];
   parser.delegate = self;
   [parser parse:data];
   if (parser.parserError) {
   NSLog(@"Error:\n%@", parser.parserError);
   }

   parser.delegate = nil;

   // Include delegate methods from YAJLParserDelegate
   - (void)parserDidStartDictionary:(YAJLParser *)parser { }
   - (void)parserDidEndDictionary:(YAJLParser *)parser { }

   - (void)parserDidStartArray:(YAJLParser *)parser { }
   - (void)parserDidEndArray:(YAJLParser *)parser { }

   - (void)parser:(YAJLParser *)parser didMapKey:(NSString *)key { }
   - (void)parser:(YAJLParser *)parser didAdd:(id)value { }
   @endcode
 */
@interface YAJLParser : NSObject
@property (weak, nonatomic) id <YAJLParserDelegate> delegate;
@property (readonly, strong, nonatomic) NSError * _Nullable parserError;
@property (readonly, nonatomic) YAJLParserOptions parserOptions;
@property (readonly, nonatomic) unsigned int bytesConsumed;

/*!
   Create parser with data and options.
   @param parserOptions Parser options
   - YAJLParserOptionsNone: No options
   - YAJLParserOptionsAllowComments: Javascript style comments will be allowed in the input (both /&asterisk; &asterisk;/ and //)
   - YAJLParserOptionsCheckUTF8: Invalid UTF8 strings will cause a parse error
   - YAJLParserOptionsStrictPrecision: If YES will force strict precision and return integer overflow error
 */
- (instancetype)initWithParserOptions:(YAJLParserOptions)parserOptions NS_DESIGNATED_INITIALIZER;

/*!
   Parse data.

   If streaming, you can call parse multiple times as long as
   previous calls return YAJLParserStatusInsufficientData.

   @param data
   @result Parser status
   - YAJLParserStatusNone: No status
   - YAJLParserStatusOK: Parsed OK
   - YAJLParserStatusInsufficientData: There was insufficient data
   - YAJLParserStatusError: Parser errored
 */
- (YAJLParserStatus)parse:(NSData *)data;
@end
NS_ASSUME_NONNULL_END
