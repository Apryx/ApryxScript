package context;

import generation.JSGenerator;

import java.util.List;

public class Function implements JSGenerator{
	
	private String name;
	private List<FunctionArgument> arguments;
	
	public Function(String name, List<FunctionArgument> arguments){
		this.name = name;
		this.arguments = arguments;
	}
	
	public List<FunctionArgument> getArguments() {
		return arguments;
	}
	
	public String getName() {
		return name;
	}

	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();
		
		builder.append("function ");
		
		return builder.toString();
	}
	
	
}
