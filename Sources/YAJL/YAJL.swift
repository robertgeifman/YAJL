@_exported import yajl_objc

public extension YAJLParser {
}

public extension YAJLDocument {
	func parse(_ data: Data) throws -> YAJLParserStatus {
		var error: NSError?
		let result = parse(data, error: &error)
		if let error = error {
			throw error
		}
		return result
	}
}
