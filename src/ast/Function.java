package ast;

import java.util.List;

import statement.Context;

public class Function extends Type {
	
	private String name;
	private Type type;
	private List<NameAndType> args;
	private Context body;
	
	public Function(String name, Type type, List<NameAndType> args){
		super(name);
		
		this.name = name;
		this.type = type;
		this.args = args;
		
		body = new Context();
		
		for(NameAndType t : args){
			body.add(new Variable(t.getName(),t.getType(),true));
		}
	}
	
	public void typeCheck() {
		getBody().typeCheck();
	}
	
	public Context getBody() {
		return body;
	}
	
	public void setBody(Context body) {
		this.body = body;
	}
	
	public String getName() {
		return name;
	}
	
	public Type getType() {
		return type;
	}
	
	@Override
	public String toString() {
		return super.toString();
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
		
		
		builder.append(body.toXML());
		
		builder.append("</function>");
		
		return builder.toString();
	}
}
