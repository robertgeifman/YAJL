import XCTest
@testable import YAJL

final class YAJLTests: XCTestCase {
    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct
        // results.
        XCTAssertEqual(YAJL().text, "Hello, World!")
    }

    static var allTests = [
        ("testExample", testExample),
    ]
}
