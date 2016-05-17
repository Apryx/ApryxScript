package statement;

public class ClassType extends Type{
	
	private String name;
	//TODO add the class here
	
	public ClassType(String name){
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
}
