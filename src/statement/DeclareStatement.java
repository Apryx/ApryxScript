package statement;

public class DeclareStatement extends Statement{
	
	private String name;
	private String type;
	
	public DeclareStatement(String name, String type){
		this.name = name;
		this.type = type;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
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
