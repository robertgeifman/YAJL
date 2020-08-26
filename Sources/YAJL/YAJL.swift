@_exported import yajl_objc

// MARK: - YAJLDocument
public extension YAJLDocument {
	internal final class MyDelegate: NSObject, YAJLDocumentDelegate {
		var entries = [Any]()
		func document(_ document: YAJLDocument, didAdd dictionary: [AnyHashable: Any]) {
			guard nil == document.currentKeyPath else { return }
			entries.append(dictionary)
	    }
	}
    convenience init(data: Data, parserOptions: YAJLParserOptions) throws {
		var error: NSError?
		self.init(data: data, parserOptions: parserOptions, error: &error)
		if let error = error {
			throw error
		}
    }
    convenience init(data: Data, parserOptions: YAJLParserOptions, capacity: Int) throws {
		var error: NSError?
		self.init(data: data, parserOptions: parserOptions, capacity: capacity, error: &error)
		if let error = error {
			throw error
		}
    }

	@discardableResult
	func parse(_ data: Data) throws -> YAJLParserStatus {
		var error: NSError?
		let result = parse(data, error: &error)
		if let error = error {
			throw error
		}
		return result
	}
	func parseRootEntries(_ data: Data) throws -> [Any] {
		let previousDelegate = delegate
		defer { delegate = previousDelegate }

		let myDelegate = MyDelegate()
		delegate = myDelegate

		try parse(data)
		return myDelegate.entries
	}
}

// MARK: - YAJLParserStatus
extension YAJLParserStatus: CustomStringConvertible {
	public var description: String {
		switch rawValue {
		case 0: return "none"
		case 1: return "ok"
		case 2: return "insufficientData"
		case 3: return "error"
		default: return "\(rawValue)"
		}
	}
}
