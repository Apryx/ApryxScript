package statement;

public class Variable {
	
	private String name, type;
	private boolean argument;

	public Variable(String name, String type){
		this(name, type, false);
	}
	
	public Variable(String name, String type, boolean argument){
		this.name = name;
		this.type = type;
		this.argument = argument;
	}
	
	public String getType() {
		return type;
	}
	
	public String getName() {
		return name;
	}
	
	public boolean isArgument() {
		return argument;
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		//<declare name="a" type="int" />
		
		builder.append("<declare name=\"");
		builder.append(name);
		builder.append("\" type=\"");
		builder.append(type);
		builder.append("\" />");
		
		return builder.toString();
	}
}
