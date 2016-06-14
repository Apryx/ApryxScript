package context;

import generation.JSGenerator;

import java.util.List;

public class Function implements JSGenerator{
	
	private String name;
	private List<ApryxVariable> arguments;
	private Context context;
	
	public Function(String name, List<ApryxVariable> arguments, Context statement){
		this.name = name;
		this.arguments = arguments;
		this.context = statement;
	}
	
	public List<ApryxVariable> getArguments() {
		return arguments;
	}
	
	public String getName() {
		return name;
	}
	
	public Context getStatement() {
		return context;
	}
	
	public void setArguments(List<ApryxVariable> arguments) {
		this.arguments = arguments;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public void setStatement(Context c) {
		this.context = c;
	}
	
	public Type getFunctionType(){
		return null; // TODO implement this
	}

	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();
		
		builder.append("function ");
		
		if(name != null)
			builder.append(name);
		
		builder.append('(');
		
		for(int i = 0; i < arguments.size(); i++){
			builder.append(arguments.get(i).getName());
			if(i != arguments.size() - 1)
				builder.append(',');
		}
		
		builder.append(')');
		
		builder.append('{');
		
		for(int i = 0; i < arguments.size(); i++){
			if(arguments.get(i).hasDefaultValue()){
				builder.append("if(");
				builder.append(arguments.get(i).getName());
				builder.append("==undefined){");
				builder.append(arguments.get(i).getName());
				builder.append("=");
				builder.append(arguments.get(i).getDefaultValue().toJSString());
				builder.append(";}");
			}
		}
		
		if(context != null)
			builder.append(context.toJSString());
		builder.append('}');
		
		return builder.toString();
	}
	
	
}
