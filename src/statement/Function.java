package statement;

import java.util.List;

public class Function {
	
	private String name, type;
	private CodeBlock code;
	private List<NameAndType> args;
	
	public Function(String name, String type, List<NameAndType> args, CodeBlock code){
		this.name = name;
		this.type = type;
		this.code = code;
		this.args = args;
	}
	
	public String getName() {
		return name;
	}
	
	public String getType() {
		return type;
	}
	
	public CodeBlock getCode() {
		return code;
	}
	
	public List<NameAndType> getArguments() {
		return args;
	}
}
