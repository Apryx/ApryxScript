package ast;

import java.util.List;

import statement.CodeBlock;

public class Function {
	
	private String name, type;
	private CodeBlock code;
	private List<NameAndType> args;
	
	public Function(String name, String type, List<NameAndType> args, CodeBlock code){
		this.name = name;
		this.type = type;
		this.code = code;
		this.args = args;
		
		for(NameAndType t : args){
			code.add(new Variable(t.getName(),t.getType(),true));
		}
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
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		builder.append("<function name=\"");
		builder.append(name);
		builder.append("\" type=\"");
		builder.append(type);
		builder.append("\">");
		/*
		builder.append("\" arguments=\"");
		
		for(int i = 0; i < args.size(); i++){
			builder.append(args.get(i));
			
			if(i != args.size() - 1){
				builder.append(',');
			}
		}*/
		
		
		builder.append(code.toXML());
		
		builder.append("</function>");
		
		return builder.toString();
	}
}
