@_exported import yajl_objc

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

// MARK: - YAJLParser
public extension YAJLParser {
}

// MARK: - <# Mark Description #>
public extension YAJLDocument {
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
	func parse(_ data: Data) throws -> YAJLParserStatus {
		var error: NSError?
		let result = parse(data, error: &error)
		if let error = error {
			throw error
		}
		return result
	}
}
