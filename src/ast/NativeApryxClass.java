package ast;

public class NativeApryxClass extends ApryxClass{
	
	private Class<?> nat;

	public NativeApryxClass(String name, String nativeName) {
		super(name);
		try {
			this.setNative(Class.forName(nativeName));
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}

	public Class<?> getNative() {
		return nat;
	}

	public void setNative(Class<?> nat) {
		this.nat = nat;
	}

}
